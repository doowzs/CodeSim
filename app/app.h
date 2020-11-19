#ifndef APP_APP_H
#define APP_APP_H

#include <string>
#include <vector>

struct Config;
class Program;

class App {
  private:
    const bool verbose;
    const std::vector<const std::string> files;

  private:
    std::vector<Program *> programs;

  public:
    App() = delete;
    explicit App(Config *config);
    ~App();

  public:
    int run();
};

#endif//APP_APP_H
