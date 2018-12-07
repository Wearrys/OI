#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;

const int N = 2000000;
const int mo = 1e9 + 7;

int n;
int fac[N + 5], inv[N + 5];

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = (ll) res * x % mo;
        x = (ll) x * x % mo;
    }
    return res;
}

void init() {
    fac[0] = 1;
    for(int i = 1; i <= N; ++i) fac[i] = (ll) fac[i-1] * i % mo;
    inv[N] = fpm(fac[N], mo - 2);
    for(int i = N; i >= 1; --i) inv[i-1] = (ll) inv[i] * i % mo;
}

inline int binom(int x, int y) {
    if(x < 0 || y < 0 || x < y) return 0;
    return (ll) fac[x] * inv[y] % mo * inv[x - y] % mo;
}

int main() {
#ifdef Wearry 
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    init();
    scanf("%d", &n);

    int ans = (ll) fac[n-1] * (n-1) % mo;
    for(int k = 1; k < n; ++k) {
        ans = (ans - (ll) binom(n - 3 - k + 1, k) * fac[n - 1 - k] % mo * fac[k]) % mo; 
    }
    ans = (ans + mo) % mo;
    printf("%d\n", ans);

    return 0;
}
