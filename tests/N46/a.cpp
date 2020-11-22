// Author: Tianyun Zhang
// NJU-NGOJ #46 Height
#include <iostream>
using namespace std;
int n = 0, t = 0;
int main() {
  int T = 0;
  scanf("%d", &T);
  while (T--) {
    int ans = 0;
    scanf("%d", &n);
    scanf("%d", &t);
    for (int i = 1, last = 1, curr = 1, prev = n+1; i < n; ++i) {
      scanf("%d", &t);
      if (t < prev) {
        --last;
        if (last <= 0) {
          last = curr;
          curr = 0;
          ++ans;
        }
      }
      ++curr;
      prev = t;
    }
    printf("%d\n", ans);
  }
  return 0;
}