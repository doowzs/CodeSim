#include "langs/generic.h"

#include <string>
using namespace std;

Program::Program(const string file) : file(std::move(file)) {}

