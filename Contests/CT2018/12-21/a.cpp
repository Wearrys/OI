#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;

int n, d;
int a[N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d%d", &n, &d);
    for(int i = 1; i <= n; ++i) scanf("%d", a + i);

    while(d > (d & -d)) d -= (d & -d);
    for(int i = 2 * d + 1; i <= n; ++i) if(a[i] != a[i - 2 * d]) return !puts("-1");

    int ans = 0;

    n = 2 * d;
    while(n > 1) {

        static int del[N + 5], tag[N + 5];

        for(int i = 1; i <= n; ++i) {
            tag[i] = 0;
            if(i == 1) 
                del[i] = a[i] - a[n]; 
            else 
                del[i] = a[i] - a[i-1];
        }

        for(int i = 1; i <= d; ++i) {
            int step = abs(del[i] - del[i + d]);
            if(step & 1) return !puts("-1");
            else {
                ans += step / 2;
                if(del[i] > del[i + d]) {
                    del[i] -= step / 2;
                    del[i + d] += step / 2;

                    if(i <= d) {
                        tag[i] -= step / 2;
                        tag[i + d] += step / 2;
                    } else {
                        tag[i] -= step / 2;
                        tag[1] -= step / 2;
                        tag[i + d - n] += step / 2;
                    }

                } else {

                    if(i <= d) {
                        tag[i + d] -= step / 2;
                        tag[1] -= step / 2;
                        tag[i] += step / 2;
                    } else {
                        tag[i + d] -= step / 2;
                        tag[i] += step / 2;
                    }

                    del[i + d] -= step / 2;
                    del[i] += step / 2;
                }
            }
        }

        for(int i = 1; i <= n; ++i) {
            tag[i] += tag[i-1];
            a[i] += tag[i];
            if(a[i] < 0) return !puts("-1");
        }

        n >>= 1;
        d >>= 1;
    }
    printf("%d\n", ans);

    return 0;
}
