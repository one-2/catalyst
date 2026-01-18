# Catalyst: A Hardware-Agnostic Deep Learning Framework

**Author**: Stephen Elliott  
**Institution**: UNSW Sydney  
**Project**: COMP4121 Course Project (2024)  
**Status**: Incomplete, Archived

## Overview

Catalyst is a deep learning framework I designed and built to learn the architectural principles of modern deep learning systems, like PyTorch and TensorFlow. This project examines how the mathematics of neural networks are implemented and executed on hardware, through computational graphs, automatic differentiation, backpropagation, and hardware abstraction layers.

The framework develops architectural decisions from first principles, with emphasis on modularity and explicit design patterns over quick-and-dirty tricks. I originally aimed to train a GPT on the framework, but I soon realised the scope of that ambition and decided to prioritise depth of systems understanding instead. 

Over the 10-week course, I research established deep learning backends, learned C++, designed the system, and implemented substantial parts of it. This was a fantastic learning experience as an intermediate undergraduate and I am pleased to share it.

**Focus Areas:**
- Computational graph design and execution
- Hardware abstraction with strategy patterns
- Automatic differentiation and backpropagation
- Asynchronous process and hardware management


## Learning Outcomes

Beyond learning C++, this project provided systematic investigation of:

1. **Framework Design Complexity**: The translation from mathematical specification (∂L/∂w) to executable code requires addressing graph intermediate representations, memory management, execution scheduling, and numerical stability

2. **Hardware Abstraction**: Strategy patterns enable transparent operation dispatch to CPU (sequential, cached execution) versus GPU (parallel, high-bandwidth execution) contexts based on hardware characteristics

3. **HPC Software Engineering**: Complexity management through smart pointers, RAII, mutex protection, and design patterns (Strategy, Factory, Singleton) in performance-critical implementations

4. **Systems Understanding**: Machine learning as high-performance computing applications with concrete hardware constraints, memory hierarchies, and parallelisation requirements.

As a time-limited education project, I emphasised design depth over implementation breadth. I treated architectural decisions as learning opportunities rather than optimising for feature completeness or efficiency. In the end this system gave me a good understanding of deep learning backends and larger-scale system design, and prepared me to write better code in future research projects. It also opened the door to contributing to open-source HPC backends, though I discovered through the project that my interest really lies in models. Hence, I refocused my attention on models and frontier theory after this project.

## Project Evolution

**Initial objectives:** Primarily, to learn about industrial deep learning backends. In particular, by:
Designing and implementing my own framework  -> Training a GPT in it -> In this context, analysing the transformer architecture.

**Complexity was higher than I expected:** The design required much more implementation than I anticipated. With the scope and interconnectedness of a flexible system like this, core components - graph traversal algorithms, cache invalidation, pointer management, integrating libtorch - each expanded into their own engineering problems.

**I adjusted the scope:** I shifted my focus from outcomes (train a GPT) to educational benefit, especially by focusing on a strong design. My final report and system diagram focuses on this architectural understanding over chasing a complete implementation, which I believe would have taught me less about systems in general (my objective).

## Architecture

```
Model (API Layer)
    ↓
Computational Graph (CGGraph, CGNode)
    ↓
Tensor Operations (Strategy Pattern)
    ↓
CPU Strategy ← → GPU Strategy (OpenCL)
```

**Core Components:**
- **Computational Graph**: DAG-based execution with topological sorting and automatic differentiation
- **Tensor Operations**: Hardware-agnostic interface with CPU/GPU strategy implementations
- **Data Pipeline**: Dataset loading, batching, train/val/test splitting
- **Logging System**: Async JSON logging with system metrics and training diagnostics
- **GPU Infrastructure**: OpenCL kernel management (architecture defined, kernels not implemented)

See also:
- The [technical report](docs/PROJECT_REPORT_4121.pdf) for a detailed design discussion, including a review of major frameworks;
- The [architecture review](ARCHITECTURE_REVIEW.md) for a spotlight on the main features of each module, and the [system diagrams](https://www.figma.com/design/UXEFP7oxLK4gug4gUgBLbK/Catalyst-Working-Class-Diagram) for an overview of the system architecture;
- The [branch guide](docs/BRANCH_GUIDE.md) for what's on each of the dev branches.

## Implementation Status

**Completed:**
- ✓ Data handling (Dataset, DataLoader with proper splitting)
- ✓ Async logging system (multiple entry types, serialisation to JSON)
- ✓ Tensor operations interface with strategy pattern
- ✓ Comprehensive unit tests (Google Test)

**Partially Implemented:**
- ◐ Computational graph (forward/backward passes with known segfault issues)
- ◐ GPU operations infrastructure (headers and interfaces only)
- ◐ Model training loop (stubs present)

**Designed but Not Implemented:**
- ✗ Custom OpenCL kernels
- ✗ Computational graph optimisation
- ✗ Multi-device scheduling
- ✗ Distributed training (Bonzo-HPC library described in report)


## Building the repo

**Dependencies:**
- C++20 compiler
- CMake 3.18+
- LibTorch 2.5.1 (CUDA 12.4)
- OpenCL 1.2+
- Google Test (included)

```bash
# Download LibTorch
wget https://download.pytorch.org/libtorch/cu124/libtorch-cxx11-abi-shared-with-deps-2.5.1%2Bcu124.zip
unzip libtorch-*.zip

# Build
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=../libtorch ..
cmake --build . --config Release

# Run tests
ctest --output-on-failure
```

**Note**: Not all branches compile successfully. The `tensorops` branch contains the most complete tested implementation.

## Repo Structure

```
source/
├── computationgraph/    # CGGraph, CGNode (DAG execution)
├── tensorops/           # Hardware abstraction (Strategy pattern)
├── gpuops/              # OpenCL kernel infrastructure
├── datahandlers/        # Dataset, DataLoader
├── logging/             # Async logging system
├── io/                  # File I/O utilities
└── Model/               # Top-level API

tests/                   # Unit tests (Google Test)
docs/                    # Technical reports
design/                  # Figma architecture diagrams
```

## Known Issues

- Segmentation faults in multi-layer forward passes (pointer invalidation)
- Type mismatches between tensor and scalar operations in gradient updates
- OpenCL kernel source code unimplemented (infrastructure only)
- No end-to-end training loop despite component implementations

These issues are documented to indicate my progress with the implementation. The project's educational objectives have been achieved so I don't intend to resolve them.

## Related Work

Inspired by:
- **PyTorch**: Dynamic graphs, autograd
- **TensorFlow**: Grappler optimisation, XLA compilation
- **Karpathy's micrograd**: Minimal autograd reference
- **Horovod**: Distributed training patterns

Academic foundations:
- Vaswani et al., "Attention is All You Need"
- Dao et al., "FlashAttention"
- CLRS, *Introduction to Algorithms* (graph algorithms)

## License

MIT License - See LICENSE file for details.

## Contact

**GitHub**: [one-2/catalyst](https://github.com/one-2/catalyst)
