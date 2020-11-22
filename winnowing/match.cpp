#include "winnowing/interface.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Increase score based on length of sequent matchings.
double Winnowing::match(const Winnowing *A, const Winnowing *B) {
  unsigned strike = 0;
  size_t score = 0;
  size_t last_pos = 0;
  vector<size_t> last_matches;
  for (int pass = 0; pass < 2; ++pass) {
    swap(A, B);
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
      score += 1 << min(strike++, 2U);
      last_pos = matches.empty() ? 0 : pos;
      last_matches.clear();
      copy(matches.begin(), matches.end(), back_inserter(last_matches));
    }
  }
  double frac = static_cast<double>(A->size() + B->size()) * 4 - 5;
  return static_cast<double>(score) / frac * 100; // to percentage
}