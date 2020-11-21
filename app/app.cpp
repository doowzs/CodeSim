#include "app/app.h"
#include "app/config.h"

#include "langs/generic.h"
#include "langs/cpp11.h"
#include "winnowing/interface.h"

#include <iostream>
#include <iomanip>
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
    try {
      auto program = new Cpp11(file);
      program->load_contents();
      program->calculate_fingerprints();
      programs.emplace_back(program);
    } catch (errno_t ec) {
      return ec;
    }
  }
  if (programs.size() == 2) {
    const auto A = programs[0]->get_fingerprints();
    const auto B = programs[1]->get_fingerprints();
    double score = Winnowing::match(A, B);
    cout << fixed << setprecision(3) << score << endl;
  } else {
    size_t size = programs.size();
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        const auto A = programs[i]->get_fingerprints();
        const auto B = programs[j]->get_fingerprints();
        double score = Winnowing::match(A, B);
        cout << files[i] << " " << files[j] << ": "
             << fixed << setprecision(3) << score << endl;
      }
    }
  }
  cerr.clear();
  return 0;
}
