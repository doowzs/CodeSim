// Author: Michael Yan
// NJU-NGOJ #46 Height
#include <iostream>
#include <climits>

using namespace std;

#define MAXN 200005

int a[MAXN];

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }
        a[0] = INT_MAX;
        int last_layer = 1;
        int last_layer_end = 0;
        int cnt = 0;
        for(int i = 1; i < n; ++i) {
            if(a[i] < a[i - 1]) {
                if(--last_layer == 0) {
                    ++cnt;
                    last_layer = i - last_layer_end;
                    last_layer_end = i;
                }
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}
