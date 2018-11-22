#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 18;
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

namespace Poly {
    const int g = 3;

    int n;
    void init(int m) {
        n = m;
        while(n > (n & -n)) n += n & -n;
    }

    int w[N + 5], iw[N + 5];
    void getw() {
        for(int i = 1; i <= N; i <<= 1) {
            w[i] = fpm(g, (mo - 1) / i / 2);
            iw[i] = fpm(w[i], mo - 2);
        }
    }

    void dft(int *x, int ty) {
        for(int i = 0, j = 0; i < n; ++i) {
            if(i < j) swap(x[i], x[j]);
            for(int l = n >> 1; (j ^= l) < l; l >>= 1);
        }

        for(int l = 1; l < n; l <<= 1) {
            int wn = (ty > 0) ? w[l] : iw[l];

            for(int i = 0; i < n; i += (l << 1)) {
                int w = 1;
                for(int j = 0; j < l; ++j, w = 1ll * w * wn % mo) {
                    int u = x[i + j];
                    int v = 1ll * w * x[i + j + l] % mo;

                    x[i + j] = (u + v) % mo;
                    x[i + j + l] = (u - v + mo) % mo;
                }
            }
        }

        if(ty == -1) {
            int invn = fpm(n, mo - 2);
            for(int i = 0; i < n; ++i) {
                x[i] = 1ll * x[i] * invn % mo;
            }
        }
    }

    void mul(int *x, int a, int *y, int b, int *z, int c, int s) {
        static int tx[N + 5], ty[N + 5];

        for(int i = 0; i < n; ++i) {
            tx[i] = (i < a) ? x[i] : 0;
            ty[i] = (i < b) ? y[i] : 0;
        }

        dft(tx, +1), dft(ty, +1);
        for(int i = 0; i < n; ++i) tx[i] = 1ll * tx[i] * ty[i] % mo;
        dft(tx, -1);

        for(int i = 0; i < c; ++i) z[i] = (z[i] + tx[i + s]) % mo;
    }
}

int n, ta, tb;
int fac[N + 5], inv[N + 5];
int f[N + 5], t[N + 5], p[N + 5];

int binom(int x, int y) {
    return 1ll * fac[x] * inv[y] % mo * inv[x-y] % mo;
}

void init() {
    fac[0] = 1;
    for(int i = 1; i <= N; ++i) fac[i] = 1ll * fac[i-1] * i % mo;
    inv[N] = fpm(fac[N], mo - 2);
    for(int i = N; i >= 1; --i) inv[i-1] = 1ll * inv[i] * i % mo;
}

void solve(int l, int r) {
    if(l == r) { t[l] = 1ll * (t[l] + f[l]) * fpm(l, mo - 2) % mo; return; }

    int mid = (l + r) >> 1;

    solve(l, mid);

    Poly::init(r - l + 5);
    Poly::mul(t + l, mid - l + 1, p, r - l + 1, f + mid + 1, r - mid, mid - l);
    Poly::mul(f + l, mid - l + 1, t, r - l + 1, t + mid + 1, r - mid, mid - l + 1);
    Poly::mul(t + l, mid - l + 1, f, min(r - l + 1, l), t + mid + 1, r - mid, mid - l + 1);

    solve(mid+1, r);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
#endif

    init();
    scanf("%d%d%d", &n, &ta, &tb);
    for(int i = 1, a; i <= ta; ++i) scanf("%d", &a), p[a] = inv[a];
    for(int i = 1, b; i <= tb; ++i) {
        scanf("%d", &b);
        if(b) f[b + 1] = inv[b];
    }

    if(n == 1) return !puts("1");

    Poly::getw();
    solve(1, n);

    printf("%lld\n", 1ll * f[n] * fac[n-1] % mo); 

    return 0;
}
