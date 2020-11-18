#ifndef APP_APP_H
#define APP_APP_H

#include "app/config.h"

#include <string>
#include <vector>

class App {
  private:
    const bool verbose;
    const std::vector<const std::string> files;

  public:
    App() = delete;
    explicit App(Config config);
    ~App();

  public:
    int run();
};

#endif//APP_APP_H
