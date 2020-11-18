#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <string>
#include <vector>

struct Config {
  bool verbose;
  std::vector<const std::string> files;
  Config();
};

#endif//APP_CONFIG_H
