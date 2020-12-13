# CodeSim

Source code plagrism detection based on Winnowing algorithm.

## Usage

```
Usage: codesim [-vh] -- files
  - codesim a.cpp b.cpp: compare two files
  - codesim files/*.cpp: compare multiple files
```

Available options:

- `-v --verbose`: print debugging message
- `-h --help`: print help message
- `--`: indicate remaining arguments are files

## Building

This program depends on LLVM toolchain version 11.

It is only tested in macOS and Debian-based Linux distros. To compile it from source code, use instructions given below.

### Makefile Usage

- `make`: compile codesim
- `make test`: run codesim with two example files
- `make clean`: clean generated binaries

### macOS (10.15+)

The latest version of llvm can be installed with [homebrew](https://brew.sh).

```
$ brew install llvm
$ make
```

### Debian / Ubuntu

Outdated `llvm-7` from Debian official repository will not compile. We need to get stable versions from [llvm repository](https://apt.llvm.org). Update your apt repository list (usually `/etc/apt/sources.list`) to add llvm repository:

For Debian Buster (10.x):

```
deb http://apt.llvm.org/buster/ llvm-toolchain-buster-11 main
```

For Ubuntu Bionic (18.04LTS):

```
deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-11 main
```

For other distros, please refer to llvm release info.

If you have older llvm installed, purge it from your system first. Then install llvm-11 and compile. `llvm-config` will tell `make` where to find llvm libraries.

```
$ apt update
$ apt install llvm-11 llvm-11-dev clang-11 libclang-11-dev libclang-cpp11-dev
$ make
```
