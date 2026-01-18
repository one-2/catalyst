# Branch Guide

I developed Catalyst on different branches according to the module. This guide summarises their roles and contents.

## Branch Overview

| Branch      | Focus                 | Status           | Key Files                              |
| ----------- | --------------------- | ---------------- | -------------------------------------- |
| `main`      | Base implementation   | Stable           | All core infrastructure                |
| `tensorops` | Hardware abstraction  | Most complete    | `tensorops/TensorStrategy/*`           |
| `cg`        | Computational graph   | Algorithmic work | `computationgraph/CGGraph/CGGraph.cpp` |
| `GPUOps`    | OpenCL infrastructure | Headers only     | `gpuops/Kernel/*`                      |

## Branch Details

### `main` Branch

**Contents:**
- Data pipeline (Dataset, DataLoader)
- Logging (LogBook, LogEntry hierarchy)
- I/O utilities
- Basic Model container
- CGNode with LibTorch integration
- Basic tensorops wrapper

**Implemented:**
- ✓ Loading CSV datasets
- ✓ Train/val/test splitting
- ✓ Async JSON logging
- ✓ System metrics collection
- ✓ Single node forward/backward passes

**What's Missing:**
- CGGraph implementation
- Full training loop
- Multi-layer networks


### `tensorops` Branch

**Contents:**
- Complete strategy pattern implementation
- `TensorStrategy` interface (pure virtual)
- `CPUStrategy` implementation
- `GPUStrategy` implementation (delegates to LibTorch)
- `TensorOpsSelector` for runtime dispatch
- Comprehensive unit tests (Google Test)

**Implemented:**
- ✓ All tensor operations (matmul, relu, softmax, etc.)
- ✓ Runtime CPU/GPU selection
- ✓ Unit tests pass for both strategies

**What's Missing:**
- Custom OpenCL kernels (GPUStrategy uses LibTorch)
- Integration with CGGraph


### `cg` Branch

**Contents:**
- Substantial CGGraph implementation
- Layer construction (`add_neural_layer`)
- Topological sort with DFS + caching
- Forward pass with activation aggregation
- Backward pass with gradient computation
- Weight optimisation

**Implemented:**
- ✓ Single-layer graphs execute correctly
- ✓ Topological sort algorithm
- ✓ Cache invalidation on modification

**Known Issues:**
- ✗ Segfaults on multi-layer forward passes (line 99 in CGGraph.cpp)
- ✗ Type mismatch in bias updates (line 266)
- ⚠ Pointer invalidation suspected in node traversal


### `GPUOps` Branch

**Contents:**
- `Kernel` abstract base class
- `KernelFactory` for kernel creation
- `KernelManagerSingleton` interface
- `MatmulKernel` header
- `ReluKernel` header
- Empty `.txt` files for kernel source code

**Implemented:**
- ✓ Class hierarchy compiles
- ✓ Design patterns correct

**What's Missing:**
- ✗ OpenCL kernel source code
- ✗ KernelManager implementation
- ✗ Device querying
- ✗ Workgroup optimisation
- ✗ Kernel compilation/caching


## Test Coverage by Branch

| Component | Branch | Coverage |
|-----------|--------|----------|
| Dataset/DataLoader | All | ✓✓✓ Comprehensive |
| Logging | All | ✓✓✓ Comprehensive |
| TensorOps | `tensorops` | ✓✓✓ Both strategies |
| CGNode | `main` | ✓ Basic |
| CGGraph | `cg` | ✗ None |
| GPU Kernels | `GPUOps` | ✗ None |

## For Future Development

Development continuation would follow this approach:

1. Begin from `tensorops` branch (most stable foundation)
2. Port CG algorithms from `cg` branch (resolve segfaults first)
3. Implement OpenCL kernels using `GPUOps` infrastructure
4. Integrate components into a working training loop
5. Add transformer architecture.

---

For specific code questions, see inline comments or ARCHITECTURE.md technical details.
