#ifndef WINNOWING_DB_H
#define WINNOWING_DB_H

#include <string>
#include <vector>
#include <unordered_map>

struct WinnowingEntry {
  const std::string file;
  size_t position;
};

class WinnowingDatabase {
  private:
    std::unordered_map<unsigned long long, std::vector<WinnowingEntry>> mapping;

  public:
    WinnowingDatabase();
};

#endif//WINNOWING_DB_H
