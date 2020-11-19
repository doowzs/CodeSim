#include "langs/cpp11.h"

#include <string>
#include <fstream>
using namespace std;

Cpp11::Cpp11(const std::string file) : Program(std::move(file)) {}

size_t Cpp11::load_contents() {
}

