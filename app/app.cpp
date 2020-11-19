#include "app/app.h"
#include "app/config.h"

#include "langs/generic.h"
#include "langs/cpp11.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

App::App(Config *config) : verbose(config->verbose), files(config->files) {
  programs = vector<Program *>();
}

App::~App() {
  for (auto &program : programs) {
    delete program;
  }
  programs.clear();
}

int App::run() {
  if (not verbose) {
    cerr.setstate(ios_base::failbit);
  } 
  for (auto &file : files) {
    programs.emplace_back(new Cpp11(file));
  } 
  for (auto &program: programs) {
    program->load_contents();
  }
  cerr.clear();
  return 0;
}
