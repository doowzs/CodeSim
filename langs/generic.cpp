#include "langs/generic.h"
#include "winnowing/interface.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Program::Program(const string file) : file(std::move(file)), fingerprints(nullptr) {}

Program::~Program() {
  if (fingerprints != nullptr) {
    delete fingerprints;
  }
  fingerprints = nullptr;
}

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

void Program::calculate_fingerprints() {
  if (contents.empty()) {
    cerr << "Contents of " << file << " not loaded." << endl;
  }
  cerr << "Calculating fingerprints for " << file << "." << endl;
  fingerprints = new Winnowing(contents);
}

const Winnowing *Program::get_fingerprints() const {
  return fingerprints;
}
