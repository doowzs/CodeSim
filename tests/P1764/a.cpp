// Author: Tianyun Zhang
// NJU-OJ P1764 Monotonic-Stack
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
typedef pair<int, int> pii;

int main() {
  int n = 0;
  vector<int> h;
  stack<pii> s;
  scanf("%d", &n);

  h.resize(n + 2, 0);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &h[i]);
  }

  long long ans = 0;
  s.emplace(make_pair(0, 0));
  for (int pos = 1; pos <= n + 1; ++pos) {
    while (!s.empty() and s.top().second > h[pos]) {
      int r = pos - 1;
      int height = s.top().second;
      while (!s.empty() and s.top().second == height) s.pop();
      int l = s.top().first;
      ans = max(ans, 1LL * height * (r - l));
    }
    s.emplace(make_pair(pos, h[pos]));
  }
  printf("%lld\n", ans);
  return 0;
}
