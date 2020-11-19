#include "langs/cpp11.h"

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

Cpp11::Cpp11(const std::string file) : Program(std::move(file)) {}

size_t Cpp11::load_contents() {
  cerr << "Loading " << file << "." << endl;
  size_t length = load_raw_code();
  cerr << "Loaded " << file << "." << endl;
  cerr << raw_code << endl;
  return length;
}

