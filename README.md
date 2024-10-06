# Stage 1
* Basic neural network library
* Main library is a Model parent and NeuralNetwork child
* Supporting classes: Log, IO
* Supporting namespaces: MatrixOps, Vis


Build commands:
-> be in /build, then run
cmake -DCMAKE_PREFIX_PATH=path/to/libtorch path/to/project
cmake --build . --config Release
