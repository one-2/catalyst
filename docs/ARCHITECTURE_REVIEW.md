# Catalyst Architecture

This document provides technical implementation details for Catalyst's design.

## Design Philosophy

Catalyst uses explicit abstractions in the high-level design. I deliberately built more flexibly than I needed to, to better understand the structures at play in more realistic systems. For example:

- Computational graphs are represented explicitly as DAGs, rather than building DAGs implicitly with default types
- Hardware dispatch is implemented through a strategy pattern
- Memory management is all explicit, with smart pointers
- Strategy pattern for tensor operations, preparing the architecture for custom GPU kernels.

## System Layers

### 1. Model Module (Public API)

**`Model` class**: Top-level container for deep networks exposed to users of the library
- Composes `Block` objects, holding layers and activations
- Manages training state, including epoch, batch, and hardware choice
- Holds a `LogBook` for diagnostics.

```cpp
Model model(storage_dir, device, name);
model.add_block(std::make_shared<NeuralLayer>(width));
model.train(dataloader, batch_size, epochs);
```

### 2. Computational Graph Module

**`CGGraph`**: DAG of computations
- Adjacency list of nodes and connections: `std::unordered_map<SharedCGNodePtr, std::vector<SharedCGNodePtr>>`
- DFS-based topological sort for forward/backward passes, with caching and cache invalidation 
- Activations are computed node-by-node, allowing batching. Gradients are computed in reverse topological order.

**`CGNode`**: Graph node, holding in this case a neuron but flexible to allow optimisations, eg operator fusion
- Stores weights, biases, activations, gradients
- Forward: `h = σ(Wx + b)` where σ is ReLU
- Backward: Computes ∂L/∂w using chain rule
- Update: `w ← w - η∇L`.

**Key Algorithm: Topological Sort**

```cpp
std::vector<SharedCGNodePtr> topo_sort_() {
    if (is_topo_cache_valid_) return topo_forward_ordering_cache_;
    
    std::stack<SharedCGNodePtr> st;
    std::unordered_map<SharedCGNodePtr, bool> visited;
    
    std::function<void(SharedCGNodePtr)> dfs_visit = [&](SharedCGNodePtr node) {
        visited[node] = true;
        for (auto& child : graph_adj_list_[node]) {
            if (!visited[child]) dfs_visit(child);
        }
        st.push(node);  // Post-order insertion
    };
    
    for (auto& pair : graph_adj_list_) {
        if (!visited[pair.first]) dfs_visit(pair.first);
    }
    
    // Stack is reverse topological order; invert for forward order
    std::vector<SharedCGNodePtr> forward_ordering;
    while (!st.empty()) {
        forward_ordering.push_back(st.top());
        st.pop();
    }
    
    topo_forward_ordering_cache_ = forward_ordering;
    is_topo_cache_valid_ = true;
    return forward_ordering;
}
```

**Cache Invalidation**: Any graph modification sets `is_topo_cache_valid_ = false`.

### 3. Tensor Operations Module

**Strategy Pattern for Hardware Abstraction**

```cpp
// Interface
class TensorStrategy {
public:
    virtual TensorPtr matmul(TensorPtr a, TensorPtr b) = 0;
    virtual TensorPtr relu(TensorPtr a) = 0;
    // ... other operations
};

// Selector
class TensorOpsSelector {
    std::unique_ptr<TensorStrategy> strategy;
public:
    TensorOpsSelector(bool use_gpu) {
        strategy = use_gpu ? std::make_unique<GPUStrategy>()
                           : std::make_unique<CPUStrategy>();
    }
};
```

**CPUStrategy**: Delegates to LibTorch CPU operations.
**GPUStrategy**: Intended for custom OpenCL kernels; currently delegates to LibTorch as a placeholder.

### 4. GPU Operations Module
**`Kernel`**: Abstract base for OpenCL kernels
- Stores source code, workgroup size/count
- Virtual `compile()` method for JIT compilation.

**`KernelFactory`**: Creates kernel instances
- Static method `build_kernel(type, workgroup_size, workgroup_count)`
- Returns the requested subclass (MatmulKernel, ReluKernel) instantiated on CPU or GPU.

**`KernelManagerSingleton`**: A global kernel cache
- Device querying and workgroup optimisation
- Kernel compilation and caching (avoids recompilation)
- Enqueue/dequeue for GPU execution.

**Note:** Kernel source (.cl) files are designed and stubbed but not implemented.

## Supporting Systems

### Data Pipeline

**`Dataset`**: Loads CSV, splits into train/val/test
- Constructor: `Dataset(path, target_variable_index)`
- Split: `split(train_frac, val_frac, test_frac)` returns array of 3 datasets
- Handles integer underflow from float→int conversion.

**`DataLoader`**: Iterator over dataset
- `get_next_observation()` returns `{input: Tensor, target: Tensor}`
- Automatic reset when exhausted.

### Logging System

**Async Design**: Logging doesn't block training
```cpp
void log_async(const LogEntry& log_entry) {
    auto log_task = std::async(std::launch::async, [this, log_entry]() {
        add_log_to_map(log_entry);         // In-memory
        write_log_to_storage(log_entry);   // Disk
    });
    // Returns immediately
}
```

**Thread Safety**: Mutex on shared log map
```cpp
void add_log_to_map(const LogEntry& log) {
    std::mutex logs_mutex;
    std::lock_guard<std::mutex> lock(logs_mutex);
    logs_map[log.get_type()].push_back(log);
}
```

**LogEntry Types**: SystemLogEntry, CheckpointLogEntry, EvaluationLogEntry, DebugLogEntry.

**Serialisation**: Uses Cereal library for JSON output.

## Memory Management

**Smart Pointers Throughout**: We practice good memory management. There is no `new`/`delete` in the application code.
- `std::shared_ptr<CGNode>` for graph nodes (whose ownership is shared to allow asynchronous execution on distributed setups)
- `std::shared_ptr<torch::Tensor>` for tensor data
- `std::unique_ptr<TensorStrategy>` for strategy (single ownership)


## Testing Strategy

**Unit Tests Using Google Test):**
- `test_dataset.cpp`: Split logic, underflow handling
- `test_dataloader.cpp`: Iterator behavior, reset
- `test_logbook.cpp`: Async logging, serialisation
- `test_TensorOpsSelector_using_CPUStrategy.cpp`: All tensor ops
- `test_TensorOpsSelector_using_GPUStrategy.cpp`: GPU dispatch

**Integration Tests**: Not implemented. Planned for testing the full training cycle.

## Known Issues
1. **CGGraph Segfaults**: Pointer invalidation during multi-layer traversal
   - May be caused by incorrect shared_ptr lifetimes
   - Needs review of pointers in layer construction.

2. **Type Mismatches**: In gradient updates.

3. **No Graph Validation**: Accepts cyclic graphs (will infinite loop)
   - This was a design choice as we are only dealing in feedforward networks, but we could add cycle detection and connectivity checks if the system was expanded.

4. **Kernel Module Incomplete**: 
   - MatmulKernel, ReluKernel headers exist
   - OpenCL source files empty
   - KernelManager device queries unfinished.

1. **Missing Error Handling**: No input validation, assumes valid data.

## Design Decisions

### DAG Representation for Computational Graphs
- This is a natural representation of data dependencies
- Topological sort determines execution order
- Reverse topological sort enables backpropagation
- It supports future graph optimisations (fusion, pruning)

### Strategy Pattern for Hardware Abstraction
- We can do runtime device selection without recompilation, like PyTorch
- Flexible - easily extensible to new backends (TPU, custom accelerators)
- Transparent to model code, giving a consistent API and good abstraction
- Trivial testing of our custom implementation against major backends

### LibTorch as Fallback Implementation
- Provides correct reference implementations
- Handles edge cases (broadcasting, numerical stability)
- Allows focus on architecture over low-level debugging
- Enables incremental replacement with custom kernels

### Asynchronous Logging
- Training becomes I/O bound with synchronous logging
- Instead, an asynchronous approach maintains throughput
- Implementation is simple with std::async and mutex

### C++ Implementation Without Python Frontend
- Project objective: understand C++ DL/HPC systems implementations
- Python binding introduces a lot of complexity
- Python API could be added as an extension


## Performance Considerations

I moved on from the project before finishing the implementation, so the system is not optimised for performance:
- No benchmarking performed
- No profiling-guided optimisation
- LibTorch fallback provides adequate baseline performance
- Custom kernels would improve GPU utilisation

Potential optimisations for future work:
- Memory pooling for allocation reuse
- Operator fusion (e.g., matmul+relu)
- Mixed precision (FP16 forward pass, FP32 gradients)
- Gradient accumulation to reduce update frequency

## Future Architectural Extensions

Potential development directions:

1. **Graph Compilation**: Translate DAG to an intermediate representation for optimisation before execution. Operator fusion, for instance, would be interesting
2. **Checkpointing**: Implement save/restore on graph state using existing Cereal logging
3. **Distributed Training**: Add MPI support (Bonzo-HPC, see report) for multi-node training
4. **JIT Compilation**: Runtime kernel specialisation based on tensor shapes.

---

For questions about specific design decisions, see inline comments in source code or technical report.
