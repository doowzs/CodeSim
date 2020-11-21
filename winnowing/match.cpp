#include "winnowing/interface.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

double Winnowing::match(const Winnowing *A, const Winnowing *B) {
  size_t count = 0;
  for (auto [pos, hash] : A->hashes) {
    if (not B->find(hash).empty()) {
      ++count;
      cerr << "Match hash [" << hash << "] on pos [" << pos << "] of A." << endl;
    } else {
      cerr << "NO Match [" << hash << "] on pos [" << pos << "] of A." << endl;
    }
  }
  return count;
}