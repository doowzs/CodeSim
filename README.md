# CodeSim

Source code plagrism detection based on Winnowing algorithm.

```
Usage: codesim [-vh] -- files
  - codesim a.cpp b.cpp: compare two files
  - codesim files/*.cpp: compare multiple files
```

## Building

### macOS

```
$ brew install llvm
$ make
```

### Debian / Ubuntu

Outdated llvm-7 from Debian repository will not compile.

We need to get stable versions from [llvm repository](https://apt.llvm.org).

```
deb http://apt.llvm.org/buster/ llvm-toolchain-buster-11 main
```

```
$ apt install llvm-11 llvm-11-dev clang-11 libclang-11-dev libclang-cpp11-dev
$ make
```
