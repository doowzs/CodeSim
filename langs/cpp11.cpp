#include "langs/cpp11.h"

#include <clang/Frontend/ASTUnit.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/raw_os_ostream.h>
using namespace clang;
using namespace clang::tooling;
using namespace llvm;

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

Cpp11::Cpp11(const string file) :
  Program(move(file)),
  stream(raw_os_ostream(cerr)) {}

size_t Cpp11::load_contents() {
  cerr << "Loading " << file << "." << endl;
  size_t length = load_raw_code();
  cerr << "Loaded " << file << "." << endl;

  auto consumer = new DiagnosticConsumer();
  const vector<string> cx_args = {
    "-E", "-x", "c++", "-std=c++11", "-pedantic"
#ifdef LLVM_PREFIX
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
    , "-I" TOSTRING(LLVM_PREFIX) "/include/c++/v1/"
    , "-I" TOSTRING(LLVM_PREFIX) "/lib/clang/11.0.0/include"
#undef TOSTRING
#undef STRINGIFY
#endif
  };
  auto unit = buildASTFromCodeWithArgs(raw_code, cx_args, file, "clang-tool", make_shared<PCHContainerOperations>(), getClangStripDependencyFileAdjuster(),FileContentMappings(), consumer);
  if (unit == nullptr) {
    cerr << "Failed to build AST for " << file << "." << endl;
    return 0;
  }

  cerr << "Built AST for " << file << "." << endl;
  unit->visitLocalTopLevelDecls((void*)this,
    [](void *context, const Decl *D) -> bool {
      D->print(((Cpp11 *)context)->stream);
      return true;
    }
  );

  return length;
}

