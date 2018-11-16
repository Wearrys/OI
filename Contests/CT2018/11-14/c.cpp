#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define debug(...) fprintf(stderr, __VA_ARGS__)

const int N = 1 << 20;
const int mo = 998244353;

inline int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = (ll) res * x % mo;
        x = (ll) x * x % mo;
    }
    return res;
}

namespace Poly {
    const int g = 3;

    int n;
    void init(int m) {
        n = m;
        while(n > (n & -n)) n += (n & -n);
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
                for(int j = 0; j < l; ++j, w = (ll) w * wn % mo) {
                    int u = x[i + j];
                    int v = (ll) x[i + j + l] * w % mo;

                    x[i + j] = (u + v) % mo;
                    x[i + j + l] = (u - v + mo) % mo;
                }
            }
        }

        if(ty == -1) {
            int invn = fpm(n, mo - 2);
            for(int i = 0; i < n; ++i) {
                x[i] = (ll) x[i] * invn % mo;
            }
        }
    }

    void mul(int *a, int la, int *b, int lb, int *c) {
        static int tx[N + 5], ty[N + 5];

        init(la + lb - 1);
        for(int i = 0; i < n; ++i) {
            tx[i] = (i < la) ? a[i] : 0;
            ty[i] = (i < lb) ? b[i] : 0;
        }

        dft(tx, +1), dft(ty, +1);
        for(int i = 0; i < n; ++i) tx[i] = (ll) tx[i] * ty[i] % mo;
        dft(tx, -1);

        for(int i = 0; i < la + lb - 1; ++i) {
            c[i] = tx[i];
        }
    }
}

int pool[N << 5], *cur = pool;

struct poly_t {
    int l, *a;
    int &operator [] (int x) { return a[x]; }
    int operator [] (int x) const { return a[x]; }
    poly_t(int _l): l(_l) { a = cur, cur += l + 1; }
    poly_t(int _l, int *_a): l(_l) { 
        a = cur, cur += l + 1; 
        for(int i = 0; i < l; ++i) a[i] = _a[i];
    }
};

poly_t mul(poly_t a, poly_t b) {
    poly_t c(a.l + b.l - 1);
    Poly::mul(a.a, a.l, b.a, b.l, c.a);
    return c;
}

bool operator < (const poly_t& a, const poly_t& b) {
    return a.l > b.l;
}

priority_queue <poly_t> q;

int n;
int c[N + 5];
int fac[N + 5], inv[N + 5];

inline int binom(int x, int y) { 
    if(x < 0 || y < 0 || x < y) return 0;
    return (ll) fac[x] * inv[y] % mo * inv[x - y] % mo; 
}

inline int f(int x, int y) {
    return binom(x + y - 1, y + y - 1);
}

void init() {
    fac[0] = 1;
    for(int i = 1; i <= N; ++i) fac[i] = (ll) fac[i-1] * i % mo;
    inv[N] = fpm(fac[N], mo - 2);
    for(int i = N; i >= 1; --i) inv[i-1] = (ll) inv[i] * i % mo;
}

int s;
int g[N + 5], h[N + 5], coe[N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    init();

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", c + i), s += c[i];

    static int tx[N + 5], ty[N + 5];
    for(int i = 1; i <= c[1]; ++i) tx[i] = (ll) f(c[1], i) * fac[i-1] % mo * fpm(i, mo - 2) % mo;
    for(int i = 0; i <= c[1]; ++i) ty[c[1] - i] = (ll) ((i&1) ? mo-1 : 1) * inv[i] % mo;

    Poly::mul(tx, c[1] + 1, ty, c[1] + 1, g);
    for(int i = 1; i <= c[1]; ++i) g[i] = (ll) g[i + c[1]] * inv[i-1] % mo;

    g[c[1] + 1] = g[c[1] + 2] = 0;
    for(int i = 0; i <= c[1]; ++i) {
        g[i] = ll(g[i + 1] - g[i + 2] + mo) * inv[i] % mo;
    }

    q.push(poly_t(c[1] + 1, g));
    
    for(int i = 2; i <= n; ++i) {

        for(int j = 1; j <= c[i]; ++j) tx[j] = (ll) f(c[i], j) * fac[j-1] % mo;
        for(int j = 0; j <= c[i]; ++j) ty[c[i] - j] = (ll) ((j&1) ? mo-1 : 1) * inv[j] % mo;

        Poly::mul(tx, c[i] + 1, ty, c[i] + 1, coe);

        coe[0] = 0;
        for(int j = 1; j <= c[i]; ++j) coe[j] = (ll) coe[j + c[i]] * inv[j] % mo * inv[j-1] % mo;

        q.push(poly_t(c[i] + 1, coe));
    }

    while(q.size() > 1) {
        poly_t a = q.top(); q.pop();
        poly_t b = q.top(); q.pop();
        poly_t c = mul(a, b); q.push(c);
    }

    int ans = 0;
    for(int i = 0; i <= s; ++i) {
        ans = (ans + (ll) q.top()[i] * fac[i]) % mo;
    }
    printf("%lld\n", (ll) ans * s % mo);

    return 0;
}
