#ifndef LANGS_GENERIC_H
#define LANGS_GENERIC_H

#include <string>

class Program {
  private:
    const std::string file;

  private:
    std::string contents;

  public:
    Program() = delete;
    Program(const std::string file);

  public:
    virtual size_t load_contents() = 0;
};

#endif//LANGS_GENERIC_H
