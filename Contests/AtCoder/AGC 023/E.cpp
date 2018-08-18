#include <bits/stdc++.h>

typedef long long ll;

using std::pair;
using std::vector;
using std::string;

#define pb(a) push_back(a)
#define mp(a, b) std::make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)

const int N = 200000;
const int mo = 1e9 + 7;

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1) 
            res = (ll) res * x % mo;
        x = (ll) x * x % mo;
    }
    return res;
}

int n, s = 1;
int a[N + 5], d[N + 5];
int lim[N + 5], cnt[N + 5];

namespace BIT {
    int c[N + 5];

    void clear() {
        memset(c, 0, sizeof c);
    }
    void modify(int x, int y) {
        for( ; x <= N; x += x & -x) {
            c[x] = (c[x] + y) % mo;
        }
    }
    int query(int x) {
        int res = 0;
        for( ; x > 0; x -= x & -x) {
            res = (res + c[x]) % mo;
        }
        return res;
    }
    inline int query(int x, int y) {
        return query(y) - query(x - 1);
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", a + i), ++ cnt[a[i]];
    for(int i=n-1; i >= 1; --i) cnt[i] = cnt[i] + cnt[i + 1] - 1;

    d[0] = 1;
    for(int i = 1; i <= n; ++i) {
        s = (ll) s * cnt[i] % mo;
        if(cnt[i] <= 0) return !puts("0");

        if(cnt[i] > 1) {
            lim[i] = lim[i-1];
            d[i] = (ll) d[i-1] * (cnt[i] - 1) % mo * fpm(cnt[i], mo - 2) % mo;
        } else {
            lim[i] = i;
            d[i] = d[i-1];
        }
    }
    
    int ans = 0;
    for(int i = 1; i <= n; ++i) {
        ans = (ans + (ll) d[a[i]] * s % mo * BIT::query(lim[a[i]], a[i])) % mo;
        BIT::modify(a[i], fpm(d[a[i]], mo - 2));
    }

    BIT::clear();
    for(int i = 1; i <= n; ++i) {
        ans = (ans + (ll) 2 * s * (i - 1 - BIT::query(a[i]))) % mo;
        BIT::modify(a[i], 1);
    }

    BIT::clear();
    for(int i = n; i >= 1; --i) {
        ans = (ans - (ll) d[a[i]] * s % mo * BIT::query(lim[a[i]], a[i] - 1)) % mo;
        BIT::modify(a[i], fpm(d[a[i]], mo - 2));
    }

    ans = (ll) (ans + mo) * ((mo + 1) >> 1) % mo;
    printf("%d\n", ans);

    return 0;
}
