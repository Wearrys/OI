#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2000000;

template <typename T> T read(T& x) {
    T f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

int n;
ll k, ans;
ll w[N + 5];

int x[N + 5], y[N + 5];
int c[N + 5][2], sz[N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(k);
    for(int i = 1; i < n; ++i) {
        static int p;
        read(p), read(w[i]); 
        -- p; w[i] ^= w[p];
    }

    fill(x, x + n, 1);
    fill(y, y + n, 1);

    for(int i = 61; i >= 0; --i) {

        int tot = 1;
        memset(c, 0, sizeof c);
        memset(sz, 0, sizeof sz);

        for(int j = 0; j < n; ++j) {
            bool d = (w[j] >> i & 1);

            if(!c[x[j]][d]) {
                c[x[j]][d] = ++ tot;
            }
            ++ sz[x[j] = c[x[j]][d]];
        }

        ll cnt = 0;

        for(int j = 0; j < n; ++j) {
            bool d = (w[j] >> i & 1);
            cnt += sz[c[y[j]][d]];
        }

        if(cnt < k) {
            k -= cnt;
            ans ^= (1ll << i);

            for(int j = 0; j < n; ++j) {
                bool d = (w[j] >> i & 1);
                y[j] = c[y[j]][d ^ 1];
            }
        } else {
            for(int j = 0; j < n; ++j) {
                bool d = (w[j] >> i & 1);
                y[j] = c[y[j]][d];
            }
        }
    }
    printf("%lld\n", ans);

    return 0;
}
