#ifndef LANGS_CPP11_H
#define LANGS_CPP11_H

#include "langs/generic.h"

#include <llvm/Support/raw_os_ostream.h>

#include <string>

class Cpp11 : public Program {
  public:
    llvm::raw_os_ostream stream;

  public:
    Cpp11() = delete;
    Cpp11(const std::string file);
    ~Cpp11() = default;

  public:
    size_t load_contents() override;
};

#endif//LANGS_CPP11_H
