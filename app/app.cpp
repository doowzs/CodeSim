#include "app/app.h"
#include "app/config.h"

#include <string>
#include <vector>
using namespace std;

App::App(Config config) :
  verbose(config.verbose),
  files(std::move(config.files)) {}

App::~App() {}

int App::run() {
  return 0;
}
