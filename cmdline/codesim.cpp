#include "cmdline/codesim.h"
#include "app/app.h"
#include "app/config.h"

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

int main(int argc, const char **argv) {
  Config config;
  if (!try_parse_cmdline_args(argc, argv, &config)) {
    print_usage_and_exit();
  }
  App app(&config);
  return app.run();
}

void print_usage_and_exit [[noreturn]] () {
  cerr << "Usage: codesim [-vh] -- files" << endl;
  exit(1);
}

bool try_parse_cmdline_args(int argc, const char **argv, Config *config) {
#define PUSH_FILE(f) config->files.emplace_back(string(f))
  int i = 1;
  for (; i < argc; ++i) {
    if (!strcmp(argv[i], "-h")) {
      return false;
    } else if (!strcmp(argv[i], "-v")) {
      config->verbose = true;
    } else if (!strcmp(argv[i], "--")) {
      break;
    } else {
      PUSH_FILE(argv[i]);
    }
  }
  for (; i < argc; ++i) PUSH_FILE(argv[i]);
#undef PUSH_FILE
  return config->files.size() >= 2;
}
