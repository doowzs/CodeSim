#include "winnowing/database.h"

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

WinnowingDatabase::WinnowingDatabase() {
  mapping = unordered_map<unsigned long long, vector<WinnowingEntry>>();
}
