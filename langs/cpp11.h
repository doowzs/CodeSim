#ifndef LANGS_CPP11_H
#define LANGS_CPP11_H

#include "langs/generic.h"

#include <string>

class Cpp11 : public Program {
  public:
    Cpp11() = delete;
    Cpp11(const std::string file);

  public:
    size_t load_contents() override;
};


#endif//LANGS_CPP11_H
