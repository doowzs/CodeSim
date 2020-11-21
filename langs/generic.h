#ifndef LANGS_GENERIC_H
#define LANGS_GENERIC_H

#include <string>

class Winnowing;

class Program {
  protected:
    const std::string file;

  protected:
    std::string raw_code;
    std::string contents;
  
  private:
    Winnowing *fingerprints;

  protected:
    size_t load_raw_code();

  public:
    Program() = delete;
    Program(const std::string file);
    virtual ~Program();

  public:
    virtual size_t load_contents() = 0;
    void calculate_fingerprints();
    const Winnowing *get_fingerprints() const;
};

#endif//LANGS_GENERIC_H
