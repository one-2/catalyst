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

- Loading CSV datasets
- Train/val/test splitting
- ASync JSON logging
- System metrics collection
- Single node forward/backward passes

**What's Missing:**
- CGGraph implementation
- Full training loop
- Multi-layer networks


### `tensorops` Branch

**Contents:**

- All tensor operations (matmul, relu, softmax, etc.)
- Runtime CPU/GPU selection
- Unit tests pass for both strategies

**What's Missing:**
- Custom OpenCL kernels (GPUStrategy uses LibTorch)
- Integration with CGGraph


### `cg` Branch

**Contents:**

- Layer construction (`add_neural_layer`)
- Topological sort with DFS + caching
- Forward pass with activation aggregation
- Backward pass with gradient computation
- Weight optimisation
- Cache invalidation on change to graph

**Known Issues:**
- Segfaults on multi-layer forward passes (line 99 in CGGraph.cpp)
- Type mismatch in bias updates (line 266)
- Pointer invalidation suspected in node traversal


### `GPUOps` Branch

**Contents:**
- Class hierarchy compiles
- Design patterns specified

**What's Missing:**
- Kernel implementations in OpenCL
- KernelManager implementation
- Device querying
- Workgroup optimisation
- Kernel compilation/caching


## Test Coverage by Branch

| Component | Branch | Coverage |
|-----------|--------|----------|
| Dataset/DataLoader | All | ✓✓✓ Comprehensive |
| Logging | All | ✓✓✓ Comprehensive |
| TensorOps | `tensorops` | ✓✓✓ Both strategies |
| CGNode | `main` | ✓ Basic |
| CGGraph | `cg` | ✗ None |
| GPU Kernels | `GPUOps` | ✗ None |

