#include "app/app.h"
#include "app/config.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

App::App(Config config) : verbose(config.verbose), files(std::move(config.files)) {
  if (not verbose) {
    cerr.setstate(ios_base::failbit);
  } 
}

App::~App() {
  cerr.clear();
}

int App::run() {
  cerr << "test" << endl;
  return 0;
}
