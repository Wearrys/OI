#include <bits/stdc++.h>
using namespace std;

const int mo = 998244353;

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1) 
            res = 1ll * res * x % mo;
        x = 1ll * x * x % mo;
    }
    return res;
}

const int N = 3000000;

namespace Poly {
    const int g = 3;

    int n;
    void init(int m) {
        n = m; 
        while(n > (n & -n)) n += (n & -n);
    }

    void dft(int *x, int ty) {
        for(int i = 0, j = 0; i < n; ++i) {
            if(i < j) std::swap(x[i], x[j]);
            for(int l = n >> 1; (j ^= l) < l; l >>= 1);
        }

        for(int l = 1; l < n; l <<= 1) {
            int wn = fpm(g, (mo - 1) / l / 2);
            if(ty == -1) wn = fpm(wn, mo - 2);

            for(int i = 0; i < n; i += (l << 1)) {
                int w = 1;
                for(int j = 0; j < l; ++j) {
                    int u = x[i + j];
                    int v = 1ll * x[i + j + l] * w % mo;

                    w = 1ll * w * wn % mo;
                    x[i + j] = (u + v) % mo;
                    x[i + j + l] = (u - v + mo) % mo;
                }
            }
        }

        if(!~ty) {
            int invn = fpm(n, mo - 2);
            for(int i = 0; i < n; ++i) x[i] = 1ll * x[i] * invn % mo;
        }
    }
}

int fac[N + 5], inv[N + 5];

void init() {
    fac[0] = 1;
    for(int i = 1; i <= N; ++i) fac[i] = 1ll * fac[i-1] * i % mo;
    inv[N] = fpm(fac[N], mo - 2);
    for(int i = N; i >= 1; --i) inv[i-1] = 1ll * inv[i] * i % mo;
}

int n, m, k;
int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    init();

    cin >> n >> m >> k;

    static int p[N + 5], a[N + 5], b[N + 5];

    for(int i = 0; i <= m; ++i) a[i] = 1ll * ((i&1) ? (mo - 1) : 1) * inv[m - i] % mo * inv[i] % mo;
    for(int i = 0; i <= m; ++i) b[i] = fpm(i, m);

    Poly::init(2 * m + 1);

    Poly::dft(a, +1);
    Poly::dft(b, +1);

    for(int i = 0; i < Poly::n; ++i) a[i] = 1ll * a[i] * b[i] % mo;

    Poly::dft(a, -1);
    for(int i = 0; i <= m; ++i) p[i] = fpm(a[m - i], n);

    int ans = 0;
    for(int i = 0; i <= m; ++i) {
        p[i] = (p[i] - p[i + 1] + mo) % mo;
        ans = (ans + 1ll * p[i] * fpm(i, k)) % mo;
    }
    printf("%d\n", ans);

    return 0;
}
