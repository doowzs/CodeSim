#include "langs/cpp11.h"

#include <clang/Basic/LangOptions.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Basic/FileManager.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <llvm/Support/Host.h>
using namespace clang;

#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

// Use CompilerInstance to create preprocessors and handle source code.
// See https://github.com/loarabia/Clang-tutorial/wiki/TutorialOrig.
Cpp11::Cpp11(const string file) : Program(move(file)) {
  ci = make_shared<CompilerInstance>();
  ci->createDiagnostics();
  options = make_shared<TargetOptions>();
  options->Triple = llvm::sys::getDefaultTargetTriple();
  target = shared_ptr<TargetInfo>(TargetInfo::CreateTargetInfo(ci->getDiagnostics(), options));
  ci->setTarget(target.get());
  ci->createFileManager();
  ci->createSourceManager(ci->getFileManager());
  ci->createPreprocessor(TU_Complete);

  HeaderSearchOptions hso;
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#ifdef LLVM_PREFIX
  hso.AddPath(TOSTRING(LLVM_PREFIX) "/include/c++/v1", frontend::Angled, false, false);
  hso.AddPath(TOSTRING(LLVM_PREFIX) "/lib/clang/11.0.0/include", frontend::Angled, false, false);
#endif
#ifdef MACOS
  hso.AddPath("/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include", frontend::Angled, false, false);
#endif
#undef TOSTRING
#undef STRINGIFY
  auto &pp = ci->getPreprocessor();
  ApplyHeaderSearchOptions(pp.getHeaderSearchInfo(), hso, pp.getLangOpts(), pp.getTargetInfo().getTriple());
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
  dc.BeginSourceFile(ci->getLangOpts()); // no initializing leads to SF
  cerr << "Preprocessor prepared." << endl;

  Token t;
  do {
    pp.Lex(t);
    if (de.hasErrorOccurred()) break;
    pp.DumpToken(t);
    cerr << endl;
  } while (t.isNot(tok::eof));
  return 0;
}

