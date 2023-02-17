# Expression Template
Simple demo of expression template technique in c++

## Requirement
- python with numpy
- cmake
- clang or gcc

## How to run
```bash
cmake -DCMAKE_CXX_FLAGS=-O3 -Bbuild && make -Cbuild -j
bash run_benchmark.sh
```

This produces `result.tsv` file, which summarizes the runtime of `naive`, `lazy`, and `expr template` implementations for adding 10 vectors.

## Benchmark Result on linux-x64
![](chart.webp)
