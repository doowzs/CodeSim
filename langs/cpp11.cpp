#include "langs/cpp11.h"

#include <clang/Tooling/Tooling.h>
using namespace clang::tooling;

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

Cpp11::Cpp11(const std::string file) : Program(std::move(file)) {}

size_t Cpp11::load_contents() {
  cerr << "Loading " << file << "." << endl;
  size_t length = load_raw_code();
  cerr << "Loaded " << file << "." << endl;

  const vector<string> cx_args = {
    "-E", "-x", "c++", "-std=c++11", "-pedantic"
#ifdef LLVM_PREFIX
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
    , "-I" TOSTRING(LLVM_PREFIX) "/include/c++/v1/"
#undef TOSTRING
#undef STRINGIFY
#endif
  };
  auto unit = buildASTFromCodeWithArgs(raw_code, cx_args);
  if (unit == nullptr) {
    cerr << "Failed to build AST for " << file << "." << endl;
    return 0;
  }

  cerr << "Built AST for " << file << "." << endl;

  return length;
}

