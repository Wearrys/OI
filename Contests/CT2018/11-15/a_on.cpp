#include <bits/stdc++.h>
using namespace std;

const int N = 200000;
const int mo = 998244353;

inline int mod(int x) {
    return (x >= mo ? x - mo : (x < 0 ? x + mo : x));
}

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = 1ll * res * x % mo;
        x = 1ll * x * x % mo;
    }
    return res;
}

int n, m;
int fac[N + 5], ifac[N + 5];

inline int binom(int x, int y) {
    return 1ll * fac[x] * ifac[y] % mo * ifac[x - y] % mo;
}

inline int calc(int x) {
    return binom(n, (n + x) >> 1);
}

int main() {

    cin >> n >> m;
    if(m > n) return puts("0"), 0;

    n <<= 1;
    (m += 1) <<= 1;

    fac[0] = 1;
    for(int i = 1; i <= n; ++i) {
        fac[i] = 1ll * fac[i-1] * i % mo;
    }
    ifac[n] = fpm(fac[n], mo - 2);
    for(int i = n; i >= 1; --i) {
        ifac[i-1] = 1ll * ifac[i] * i % mo;
    }

    int sgn = -1;
    int x = -2, y = m, ans = calc(0);

    while(x >= -n || y <= n) {
        if(x >=-n) ans = mod(ans + sgn * calc(x));
        if(y <= n) ans = mod(ans + sgn * calc(y));

        sgn *= -1;
        x = m - x;
        y = -2 - y;
        std::swap(x, y);
    }

    printf("%d\n", ans);

    return 0;
}
