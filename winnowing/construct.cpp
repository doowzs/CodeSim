#include "winnowing/interface.h"

#include <string>
#include <vector>
#include <climits>
#include <unordered_map>
using namespace std;

#if !defined(BASE) || !defined(MODULO) || !defined(WINDOW)
#error "Required macros are not all defined."
#endif
#define NEXT(x) (x + 1) % WINDOW

static inline uint32_t mpow(uint32_t b, uint32_t p) {
  uint32_t r = 1;
  b = b % MODULO;
  while (p) {
    if (p & 1) {
      r = (r * b) % MODULO;
      b = (b * b) % MODULO;
    }
    p >>= 1;
  }
  return r;
}

Winnowing::Winnowing(const string &contents) {
  uint32_t h = 0U;
  uint32_t w[WINDOW] = {};
  int cur = 0, bst = 0;
  for (int i = 0; i < WINDOW; ++i) {
    w[i] = UINT32_MAX;
  }
  for (size_t pos = 0, lim = contents.length(); pos < lim; ++pos, cur = NEXT(cur)) {
    uint32_t add = static_cast<uint32_t>(contents[pos]);
    uint32_t sub = pos >= WINDOW ? static_cast<uint32_t>(contents[pos - WINDOW]) : 0;
    w[cur] = h = ((h * BASE % MODULO) + add - (sub * mpow(BASE, WINDOW) % MODULO) + MODULO) % MODULO;
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
