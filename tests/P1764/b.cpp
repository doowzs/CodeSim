// Author: Michael Yan
// NJU-OJ P1764 Monotonic-Stack
#include <assert.h>
#include <stdio.h>
#define max(a, b) ((a)>(b)?(a):(b))

struct {
  int h,x;
} sing[1005];
int idx = 0;

int main() {
  int n;
  unsigned long long ans = 0;
  scanf("%d\n", &n);
  assert(0 <= n && n <= 1000000);
  sing[0].h = 0;
  int tmp;
  for(int i = 0; i <= n; ++i) {
    if(i < n)
      scanf("%d", &tmp);
    else
      tmp = 0;
    assert(tmp <= 1000);
    int flag;
    if((flag = (sing[idx].h > tmp))) {
      do{
        ans = max(ans, 1LL * (i - sing[idx].x) * sing[idx].h);
        --idx;
      }while(sing[idx].h > tmp);
      ans = max(ans, 1LL * (i + 1 - sing[idx + 1].x) * tmp);
    }
    if(sing[idx].h != tmp) {
      ++idx;
      sing[idx].h = tmp;
      if(!flag)sing[idx].x = i;
    }
  }
  printf("%llu\n", ans);
  return 0;
}