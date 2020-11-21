#include "winnowing/interface.h"

#include <vector>
#include <unordered_map>
using namespace std;

void Winnowing::record(uint32_t hash, size_t offset) {
  if (hashes_map.find(hash) == hashes_map.end()) {
    hashes_map[hash] = vector<size_t>();
  }
  hashes.emplace_back(make_pair(offset, hash));
  hashes_map[hash].emplace_back(offset);
}

size_t Winnowing::size() const { return hashes.size(); }

const vector<size_t> Winnowing::find(uint32_t hash) const {
  auto it = hashes_map.find(hash);
  return it == hashes_map.end() ? vector<size_t>() : it->second;
}
