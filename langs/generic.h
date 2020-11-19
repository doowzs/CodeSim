#ifndef LANGS_GENERIC_H
#define LANGS_GENERIC_H

#include <string>

class Program {
  protected:
    const std::string file;

  protected:
    std::string raw_code;
    std::string contents;

  protected:
    virtual size_t load_raw_code();

  public:
    Program() = delete;
    Program(const std::string file);
    virtual ~Program() = default;

  public:
    virtual size_t load_contents() = 0;
};

#endif//LANGS_GENERIC_H
