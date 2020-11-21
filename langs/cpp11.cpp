#include "langs/cpp11.h"

#include <clang/Basic/LangOptions.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Basic/FileManager.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/PreprocessorOptions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <llvm/Support/Host.h>
using namespace clang;

#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

static const char *cx_args[] = {
  "-E", "-x", "c++", "-std=c++11", "-pedantic",
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#ifdef MACOS
  "-I/Library/Developer/CommandLineTools/usr/include/c++/v1",
  "-I/Library/Developer/CommandLineTools/usr/lib/clang/11.0.0/include",
  "-I/Library/Developer/CommandLineTools/usr/lib/clang/12.0.0/include",
  "-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include",
#elif defined LLVM_PREFIX
  "-I" TOSTRING(LLVM_PREFIX) "/include/c++/v1",
  "-I" TOSTRING(LLVM_PREFIX) "/lib/clang/11.0.0/include",
  "-I" TOSTRING(LLVM_PREFIX) "/lib/clang/12.0.0/include",
#endif
#undef TOSTRING
#undef STRINGIFY
};
#define nr_cx_args sizeof(cx_args) / sizeof(const char *)

// Use CompilerInstance to create preprocessors and handle source code.
// See https://github.com/loarabia/Clang-tutorial/wiki/TutorialOrig.
// See https://stackoverflow.com/questions/38356485/how-do-i-put-clang-into-c-mode/38445919.
// Example https://github.com/loarabia/Clang-tutorial/blob/master/CIrewriter.cpp.
Cpp11::Cpp11(const string file) : Program(move(file)) {
  ci = make_shared<CompilerInstance>();
  ci->createDiagnostics();
  CompilerInvocation::CreateFromArgs(ci->getInvocation(),
                                     ArrayRef<const char *>(cx_args, nr_cx_args),
                                     ci->getDiagnostics());
  options = make_shared<TargetOptions>();
  options->Triple = llvm::sys::getDefaultTargetTriple();
  target = shared_ptr<TargetInfo>(TargetInfo::CreateTargetInfo(ci->getDiagnostics(), options));
  ci->setTarget(target.get());
  ci->createFileManager();
  ci->createSourceManager(ci->getFileManager());
  ci->createPreprocessor(TU_Complete);
}

size_t Cpp11::load_contents() {
  cerr << "Loading " << file << "." << endl;

  auto &de = ci->getDiagnostics();
  auto &dc = ci->getDiagnosticClient();
  auto &fm = ci->getFileManager();
  auto &sm = ci->getSourceManager();
  auto &pp = ci->getPreprocessor();
  auto fe = fm.getFile(file); // llvm::ErrorOr
  if (auto ec = fe.getError()) {
    throw ec;
  }
  auto fi = sm.createFileID(fe.get(), SourceLocation(), SrcMgr::C_User);
  sm.setMainFileID(fi);
  pp.EnterMainSourceFile();
  dc.BeginSourceFile(ci->getLangOpts(), &pp); // no initializing leads to SF

  Token t;
  stringstream buf;
  do {
    pp.Lex(t);
    const auto loc = sm.getFileLoc(t.getLocation()); // for macros
    if (sm.getFileID(loc) == fi) {
      const auto k = t.getKind();
      if (tok::isAnyIdentifier(k)) {
        buf << (pp.LookAhead(0).getKind() == tok::l_paren ? "A" : "V");
      } else if (tok::isStringLiteral(k)) {
        buf << "S";
      } else if (k) {
        buf << pp.getSpelling(t);
      }
    }
  } while (t.isNot(tok::eof));

  cerr << buf.str() << endl;
  return 0;
}

