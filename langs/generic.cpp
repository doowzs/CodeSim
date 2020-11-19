#include "langs/generic.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Program::Program(const string file) : file(std::move(file)) {}

size_t Program::load_raw_code() {
  fstream fs(file);
  stringstream buffer;
  if (not fs.is_open()) {
    cerr << "Failed to open " << file << "." << endl;
    return 0;
  }
  buffer << fs.rdbuf();
  raw_code = buffer.str();
  return raw_code.size();
}
