#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 20;
const int mo = 998244353;

typedef long long ll;

int fpm(int x, int y) {
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
    void init(int len) {
        n = len;
        while((n & -n) < n) n += n & -n;
    }

    void dft(int *x, int t) {
        for(int i = 0, j = 0; i < n; ++i) {
            if(i < j) std::swap(x[i], x[j]);
            for(int l = (n >> 1); (j ^= l) < l; l >>= 1);
        }

        for(int l = 1; l < n; l <<= 1) {
            int wn = fpm(g, (mo-1) / l / 2);
            if(t == -1) wn = fpm(wn, mo - 2);

            for(int i = 0; i < n; i += (l << 1)) {
                int w = 1;
                for(int j = 0; j < l; ++j, w = 1ll * w * wn % mo) {
                    int u = x[i + j];
                    int v = 1ll * x[i + j + l] * w % mo;

                    x[i + j] = (u + v) % mo;
                    x[i + j + l] = (u + mo - v) % mo;
                }
            }
        }

        if(t == -1) {
            int invn = fpm(n, mo - 2);
            for(int i = 0; i < n; ++i) {
                x[i] = 1ll * x[i] * invn % mo;
            }
        }
    }

    void cpy(int *x, int a, int *y, int b) {
        for(int i = 0; i < b; ++i) {
            y[i] = (i < a) ? x[i] : 0;
        }
    }

    void inv(int *x, int m, int *r) {
        static int tx[N + 5], ty[N + 5];

        if(m == 1) { r[0] = fpm(x[0], mo - 2); return; }

        inv(x, (m + 1) >> 1, r); 

        init(m << 1);
        cpy(x, m, tx, n);
        cpy(r, (m + 1) >> 1, ty, n);

        dft(tx, +1), dft(ty, +1);
        for(int i = 0; i < n; ++i) tx[i] = (2ll - 1ll * tx[i] * ty[i] % mo + mo) * ty[i] % mo;

        dft(tx, -1);
        for(int i = 0; i < m; ++i) r[i] = tx[i];
    }
}

int n, m;
int f[N + 5], g[N + 5];
int t[4][N + 5], p[4][N + 5];
int a[20][N + 5], b[20][N + 5];
int c[20][N + 5], d[20][N + 5];

void init() {
    a[0][0] = 1;
    c[0][0] = 1;
    d[0][1] = mo-1;

    Poly::init(n + m + 10);
    Poly::dft(a[0], +1); Poly::dft(b[0], +1);
    Poly::dft(c[0], +1); Poly::dft(d[0], +1);

    for(int i = 1; i < 18 && (1 << i) < m; ++i) {
        for(int j = 0; j < Poly::n; ++j) {
            t[0][j] = a[i-1][j];
            t[1][j] = b[i-1][j];
            t[2][j] = c[i-1][j];
            t[3][j] = d[i-1][j];
        }

        for(int j = 0; j < Poly::n; ++j) {
            a[i][j] = 1ll * t[0][j] * (t[1][j] + t[2][j]) % mo;
            b[i][j] = (1ll * t[0][j] * t[3][j] + 1ll * t[1][j] * t[1][j]) % mo;
            c[i][j] = (1ll * t[2][j] * t[2][j] + 1ll * t[0][j] * t[3][j]) % mo;
            d[i][j] = 1ll * t[3][j] * (t[1][j] + t[2][j]) % mo;
        }
    }
}

int main() {

    scanf("%d%d", &n, &m);
    if(n < m) return puts("0"), 0;
    if(m == 1) return puts("1"), 0;
    
    init();

    memset(t, 0, sizeof t);
    for(int i = 1; i < 3; ++i) t[i][0] = 1;
    Poly::dft(t[0], +1), Poly::dft(t[1], +1);
    Poly::dft(t[2], +1), Poly::dft(t[3], +1);

    -- m;
    for(int i = 17; i >= 0; --i) if(m >> i & 1) {
        for(int j = 0; j < Poly::n; ++j) {
            p[0][j] = (1ll * t[0][j] * c[i][j] + 1ll * t[1][j] * a[i][j]) % mo;
            p[1][j] = (1ll * t[1][j] * b[i][j] + 1ll * t[0][j] * d[i][j]) % mo;
            p[2][j] = (1ll * t[2][j] * c[i][j] + 1ll * t[3][j] * a[i][j]) % mo;
            p[3][j] = (1ll * t[3][j] * b[i][j] + 1ll * t[2][j] * d[i][j]) % mo;

            for(int k = 0; k < 4; ++k) t[k][j] = p[k][j];
        }
    }
    
    for(int i = 0; i <= n; ++i) f[i] = 1;
    Poly::dft(f, +1);

    memset(p, 0, sizeof p);
    for(int i = 0; i < Poly::n; ++i) {
        p[0][i] = (t[0][i] + 1ll * f[i] * t[1][i]) % mo;
        p[1][i] = (t[2][i] + 1ll * f[i] * t[3][i]) % mo;
    }

    Poly::dft(p[1], -1);
    Poly::inv(p[1], n + 8, p[2]);

    Poly::init(n + m + 10);
    Poly::dft(p[2], +1);
    for(int i = 0; i < Poly::n; ++i) p[0][i] = 1ll * p[0][i] * p[2][i] % mo;
    Poly::dft(p[0], -1);

    printf("%d\n", p[0][n]);

    return 0;
}
