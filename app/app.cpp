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
      vector<pair<double, string>> scores;
      const auto A = programs[i]->get_fingerprints();
      for (int j = 0; j < size; ++j) {
        if (i == j) continue;
        const auto B = programs[j]->get_fingerprints();
        const double score = Winnowing::match(A, B);
        scores.emplace_back(make_pair(score, files[j]));
      }
      sort(scores.begin(), scores.end(), greater<>());
      cout << "Matches for " << files[i] << ":" << endl;
      for (auto &s : scores) {
        cout << " -> " << fixed << setprecision(3)
             << s.first << " " << s.second << endl;
      }
    }
  }
  cerr.clear();
  return 0;
}
