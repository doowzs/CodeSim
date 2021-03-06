#ifndef LANGS_CPP11_H
#define LANGS_CPP11_H

#include "langs/generic.h"

#include <string>
#include <memory>

namespace clang {
class CompilerInstance;
class DiagnosticConsumer;
class TargetOptions;
class TargetInfo;
}

class Cpp11 : public Program {
  public:
    std::unique_ptr<clang::CompilerInstance> ci;

  public:
    Cpp11() = delete;
    Cpp11(const std::string file);
    ~Cpp11() = default;

  public:
    size_t load_contents() override;
};

#endif//LANGS_CPP11_H
