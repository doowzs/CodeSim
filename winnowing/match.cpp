#include "winnowing/interface.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Increase score based on length of sequent matchings.
double Winnowing::match(const Winnowing *A, const Winnowing *B) {
  uint8_t strike = 0;
  size_t score = 0;
  size_t last_pos = 0;
  vector<size_t> last_matches;
  for (auto [pos, hash] : A->hashes) {
    const auto matches = B->find(hash);
    bool continuous = false;
    for (auto &lm : last_matches) {
      for (auto &cm : matches) {
        if (cm - lm == pos - last_pos) {
          continuous = true;
          break;
        }
      }
    }
    if (not continuous) strike = 0;
    score += matches.size() << (strike++);
    last_pos = matches.empty() ? 0 : pos;
    last_matches.clear();
    copy(matches.begin(), matches.end(), back_inserter(last_matches));
  }
  double frac = static_cast<double>(A->size() + B->size()) * 4 - 3;
  return static_cast<double>(score) / frac * 100; // to percentage
}