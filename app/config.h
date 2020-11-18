#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <vector>

struct Config {
  bool verbose;
  std::vector<const std::string> files;
};

#endif//APP_CONFIG_H
