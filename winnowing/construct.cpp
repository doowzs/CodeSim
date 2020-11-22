#include "winnowing/interface.h"

#include <iostream>
#include <string>
#include <climits>
using namespace std;

#define WINDOW 8
#define BASE 127U
#define MODULO 998244353U
#define NEXT(x) (x + 1) % WINDOW

static inline uint64_t mpow(uint64_t b, uint64_t p) {
  uint64_t r = 1;
  b = b % MODULO;
  while (p) {
    if (p & 1) {
      r = (r * b) % MODULO;
    }
    p >>= 1;
    b = (b * b) % MODULO;
  }
  return r;
}

Winnowing::Winnowing(const string &contents) {
  uint64_t h = 0U;
  uint32_t w[WINDOW] = {};
  int cur = 0, bst = 0;
  for (int i = 0; i < WINDOW; ++i) {
    w[i] = UINT32_MAX;
  }
  for (size_t pos = 0, lim = contents.length(); pos < lim; ++pos, cur = NEXT(cur)) {
    uint64_t add = static_cast<uint64_t>(contents[pos]);
    uint64_t sub = pos >= WINDOW ? static_cast<uint64_t>(contents[pos - WINDOW]) : 0;
    h = ((h * BASE % MODULO) + add - (sub * mpow(BASE, WINDOW) % MODULO) + MODULO) % MODULO;
    w[cur] = static_cast<uint32_t>(h & ((1ULL << 32U) - 1U));
    if (pos == bst) {
      for (int nex = cur; nex != cur; nex = NEXT(nex)) {
        if (w[nex] <= w[bst]) bst = nex; // rightmost minimum
      }
      record(w[bst], pos - ((bst - cur + WINDOW) % WINDOW));
    } else {
      if (w[cur] <= w[bst]) {
        bst = cur;
        record(w[bst], pos);
      }
    }
  }
}
