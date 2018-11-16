#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100;
const int B = 1 << 12;

ll ans;
int n, q;
ll lim[N + 5];
char st[N + 5][N + 5];
bitset <B> bset[10][1 << 10], tmp;

int main() {
#ifdef Wearry 
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d%d", &n, &q);
    for(int i = 0; i < q; ++i) {
        scanf("%s", st[i]);
        for(int j = 0; j < n; ++j) {
            if(st[i][j] == '0') lim[i] |= 1 << j;
            if(st[i][j] == '1') lim[i] |= 1ll << ll(30 + j);
        }
    }

    if(n <= 18) {
        for(int i = 0; i < (1 << n); ++i) {
            ll temp = 0;

            for(int j = 0; j < n; ++j) {
                if(i >> j & 1) {
                    temp |= 1ll << ll(30 + j);
                } else {
                    temp |= 1 << j;
                }
            }

            bool flag = false;
            for(int j = 0; j < q; ++j) {
                ll x = temp | lim[j];
                if((x >> 30) & x) continue;
                flag = true;
            }

            ans += flag;
        }
    } else {

        for(int i = 0; i < (1 << (n - 18)); ++i) {
            ll temp = 0;
            for(int j = 0; j < n - 18; ++j) {
                if(i >> j & 1) {
                    temp |= 1ll << ll(30 + 18 + j);
                } else {
                    temp |= 1ll << ll(18 + j);
                }
            }

            for(int j = 0; j < q; ++j) {
                ll x = temp | lim[j]; 
                if((x >> 30) & x) continue;
                bset[j / 10][1 << (j % 10)].set(i);
            }
        }

#define lowbit(x) (x & -x)

        for(int i = 0; i < 10; ++i) {
            for(int j = 1; j < (1 << 10); ++j) {
                bset[i][j] = bset[i][j ^ lowbit(j)] | bset[i][lowbit(j)];
            }
        }

        for(int i = 0; i < (1 << 18); ++i) {
            ll temp = 0;
            for(int j = 0; j < 18; ++j) {
                if(i >> j & 1) {
                    temp |= 1ll << ll(30 + j);
                } else {
                    temp |= 1 << j;
                }
            }

            tmp.reset();
            for(int j = 0; j < 10; ++j) {
                int cur = 0;
                for(int k = 0; k < 10; ++k) {
                    ll x = temp | lim[j * 10 + k];
                    if((x >> 30) & x) continue;
                    cur |= 1 << k;
                }
                tmp |= bset[j][cur];
            }
            ans += tmp.count();
        }
    }
    printf("%lld\n", ans);

    return 0;
}
