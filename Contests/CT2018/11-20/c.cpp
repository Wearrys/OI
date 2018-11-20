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

    void dft(int *x, int ty) {
        for(int i = 0, j = 0; i < n; ++i) {
            if(i < j) swap(x[i], x[j]);
            for(int l = n >> 1; (j ^= l) < l; l >>= 1);
        }

        for(int l = 1; l < n; l <<= 1) {
            int wn = fpm(g, (mo - 1) / l / 2);
            if(ty == -1) wn = fpm(wn, mo - 2);

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
}

int n, ta, tb;
int fac[N + 5], inv[N + 5];
int a[N + 5], b[N + 5], f[N + 5], t[N + 5];

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
    if(l == r) { 
        t[l] = (t[l] + f[l]) % mo; 
        return; 
    }

    int mid = (l + r) >> 1;

    solve(l, mid);

    static int tx[N + 5], ty[N + 5];

    Poly::init(r - l + 5);

    for(int i = 0; i < Poly::n; ++i) {
        tx[i] = (i <= (mid - l)) ? 1ll * t[l + i] * inv[l + i] % mo : 0;
        ty[i] = 0;
    }

    for(int i = 1; i <= ta && a[i] <= r - l; ++i) { ty[a[i]] = inv[a[i]]; }

    Poly::dft(tx, +1), Poly::dft(ty, +1);
    for(int i = 0; i < Poly::n; ++i) tx[i] = 1ll * tx[i] * ty[i] % mo;
    Poly::dft(tx, -1);

    for(int i = mid-l; i < r-l; ++i) f[i + l + 1] = (f[i + l + 1] + 1ll * tx[i] * fac[i + l]) % mo;

    for(int i = 0; i < Poly::n; ++i) {
        tx[i] = (i <= (mid - l)) ? 1ll * f[l + i] * inv[l + i - 1] % mo : 0;
        ty[i] = (i <= (r - l)) ? 1ll * t[i] * inv[i] % mo : 0;
    }

    Poly::dft(tx, +1), Poly::dft(ty, +1);
    for(int i = 0; i < Poly::n; ++i) tx[i] = 1ll * tx[i] * ty[i] % mo;
    Poly::dft(tx, -1);

    for(int i = mid-l+1; i <= r-l; ++i) t[i + l] = (t[i + l] + 1ll * tx[i] * fac[i + l - 1]) % mo;

    for(int i = 0; i < Poly::n; ++i) {
        tx[i] = (i && i <= (r - l) && i < l) ? 1ll * f[i] * inv[i - 1] % mo : 0;
        ty[i] = (i <= (mid - l)) ? 1ll * t[i + l] * inv[i + l] % mo : 0;
    }

    Poly::dft(tx, +1), Poly::dft(ty, +1);
    for(int i = 0; i < Poly::n; ++i) tx[i] = 1ll * tx[i] * ty[i] % mo;
    Poly::dft(tx, -1);

    for(int i = mid-l+1; i <= r-l; ++i) t[i + l] = (t[i + l] + 1ll * tx[i] * fac[i + l - 1]) % mo;
    solve(mid+1, r);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
#endif

    init();
    scanf("%d%d%d", &n, &ta, &tb);
    for(int i = 1; i <= ta; ++i) scanf("%d", a + i);
    for(int i = 1; i <= tb; ++i) {
        scanf("%d", b + i);
        if(b[i]) f[b[i] + 1] = 1;
    }

    if(n == 1) return !puts("1");

    std::sort(a + 1, a + ta + 1);
    
    solve(1, n);
    printf("%d\n", f[n]); 

    return 0;
}
