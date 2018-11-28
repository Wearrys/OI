#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1 << 20;
const int mo = 998244353;

#define pb push_back

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
    void init(int m) {
        n = m;
        while(n > (n & -n)) n += n & -n;
    }

    int w[N + 5], iw[N + 5];
    void getw() {
        for(int i = 1; i <= N; i <<= 1) {
            w[i] = fpm(g, (mo - 1) / 2 / i);
            iw[i] = fpm(w[i], mo - 2);
        }
    }

    void dft(int *x, int ty) {
        for(int i = 0, j = 0; i < n; ++i) {
            if(i < j) swap(x[i], x[j]);
            for(int l = n >> 1; (j ^= l) < l; l >>= 1);
        }

        for(int l = 1; l < n; l <<= 1) {
            int wn = (ty == 1) ? w[l] : iw[l];

            for(int i = 0; i < n; i += (l << 1)) {
                int w = 1;
                for(int j = 0; j < l; ++j) {
                    int u = x[i + j];
                    int v = (ll) x[i + j + l] * w % mo;

                    w = (ll) w * wn % mo;
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

    void mul(int *a, int na, int *b, int nb, int *c) {
        static int tx[N + 5], ty[N + 5];

        init(max(na, nb));
        for(int i = 0; i < n; ++i) {
            tx[i] = (i < na) ? a[i] : 0;
            ty[i] = (i < nb) ? b[i] : 0;
        }

        dft(tx, +1), dft(ty, +1);
        for(int i = 0; i < n; ++i) tx[i] = (ll) tx[i] * ty[i] % mo;
        dft(tx, -1);

        for(int i = 0; i < na + nb - 1; ++i) {
            c[i] = tx[i];
        }
    }
}

int pw[N + 5];
int fac[N + 5], inv[N + 5];

inline int binom(int x, int y) {
    return (x < 0 || y < 0 || x < y) ? 0 : (ll) fac[x] * inv[y] % mo * inv[x - y] % mo;
}

void init() {
    Poly::getw();
    pw[0] = fac[0] = 1;
    for(int i = 1; i <= N; ++i) pw[i] = pw[i-1] * 2 % mo;
    for(int i = 1; i <= N; ++i) fac[i] = (ll) fac[i-1] * i % mo;
    inv[N] = fpm(fac[N], mo - 2);
    for(int i = N; i >= 1; --i) inv[i-1] = (ll) inv[i] * i % mo;
}

void solve0(vector<int>& v0, vector<int>& v1, int n, int m) {
    v0.clear();
    v1.clear();

    for(int i = 1; i <= n; ++i) v0.pb(binom(i + m, m) - 1);
    for(int i = 1; i <= m; ++i) v1.pb(binom(i + n, n) - 1);

    reverse(v0.begin(), v0.end());
    reverse(v1.begin(), v1.end());
}

void solve1(vector<int>& v0, vector<int>& v1, vector<int>& v2, vector<int>& v3, int dx, int dy, int n, int m) {
    v2.clear(), v2.resize(n);
    v3.clear(), v3.resize(m);

    static int na, nb;
    static int tx[N + 5], ty[N + 5], tz[N + 5];

    na = (int) v0.size();
    nb = (int) v0.size() + n - 1;
    for(int i = 0; i < na; ++i) tx[na - 1 - i] = v0[i];
    for(int i = 0; i < nb; ++i) ty[i] = binom(dx + dy - 2 + i, dy - 2);
    Poly::mul(tx, na, ty, nb, tz);
    for(int i = 0; i < n; ++i) v2[i] = (v2[i] + tz[na - 1 + i]) % mo;

    na = (int) v0.size();
    nb = (int) v0.size() + m - 1;
    for(int i = 0; i < na; ++i) tx[na - 1 - i] = (ll) v0[i] * inv[dx - 1 + i] % mo;
    for(int i = 0; i < nb; ++i) ty[i] = fac[dx + dy - 2 + i];
    Poly::mul(tx, na, ty, nb, tz);
    for(int i = 0; i < m; ++i) v3[i] = (v3[i] + (ll) tz[na - 1 + i] * inv[dy - 1 + i]) % mo;
    
    na = (int) v1.size();
    nb = (int) v1.size() + n - 1;
    for(int i = 0; i < na; ++i) tx[na - 1 - i] = (ll) v1[i] * inv[dy - 1 + i] % mo;
    for(int i = 0; i < nb; ++i) ty[i] = fac[dx + dy - 2 + i];
    Poly::mul(tx, na, ty, nb, tz);
    for(int i = 0; i < n; ++i) v2[i] = (v2[i] + (ll) tz[na - 1 + i] * inv[dx - 1 + i]) % mo;

    na = (int) v1.size();
    nb = (int) v1.size() + m - 1;
    for(int i = 0; i < na; ++i) tx[na - 1 - i] = v1[i];
    for(int i = 0; i < nb; ++i) ty[i] = binom(dx + dy - 2 + i, dx - 2);
    Poly::mul(tx, na, ty, nb, tz);
    for(int i = 0; i < m; ++i) v3[i] = (v3[i] + tz[na - 1 + i]) % mo;

    reverse(v2.begin(), v2.end());
    reverse(v3.begin(), v3.end());
}

void solve2(vector<int>& v0, vector<int>& v1, vector<int>& v2, vector<int>& v3, int n, int m) {
    v2.clear(), v2.resize(n);
    v3.clear(), v3.resize(m);

    static int na, nb;
    static int tx[N + 5], ty[N + 5], tz[N + 5];

    {
        na = n;
        nb = n + m - 1;
        for(int i = 0; i < na; ++i) tx[na - 1 - i] = (ll) v0[i] * inv[i] % mo;
        for(int i = 0; i < nb; ++i) ty[i] = (ll) fac[i] * (pw[i + 1] + (mo - 1)) % mo;
        Poly::mul(tx, na, ty, nb, tz);
        for(int i = 0; i < m; ++i) v3[i] = (v3[i] + (ll) tz[na - 1 + i] * inv[i]) % mo;
    }

    {
        na = n;
        nb = n + n - 1;
        for(int i = 0; i < na; ++i) tx[na - 1 - i] = v0[i];
        for(int i = 0; i < nb; ++i) ty[i] = (i >= n-1) ? (ll) binom(i + m - n, m - 1) * (pw[i+m-n+1]+mo-1) % mo : 0;
        Poly::mul(tx, na, ty, nb, tz);
        for(int i = 0; i < n; ++i) v2[i] = (v2[i] + tz[na - 1 + i]) % mo;
    }

    {
        na = m;
        nb = n + m - 1;
        for(int i = 0; i < na; ++i) tx[na - 1 - i] = (ll) v1[i] * inv[i] % mo;
        for(int i = 0; i < nb; ++i) ty[i] = (ll) fac[i] * (pw[i + 1] + (mo - 1)) % mo;
        Poly::mul(tx, na, ty, nb, tz);
        for(int i = 0; i < n; ++i) v2[i] = (v2[i] + (ll) tz[na - 1 + i] * inv[i]) % mo;
    }

    {
        na = m;
        nb = m + m - 1;
        for(int i = 0; i < na; ++i) tx[na - 1 - i] = v1[i];
        for(int i = 0; i < nb; ++i) ty[i] = (i >= m-1) ? (ll) binom(i + n - m, n - 1) * (pw[i+n-m+1]+mo-1) % mo : 0;
        Poly::mul(tx, na, ty, nb, tz);
        for(int i = 0; i < m; ++i) v3[i] = (v3[i] + tz[na - 1 + i]) % mo;
    }

    reverse(v2.begin(), v2.end());
    reverse(v3.begin(), v3.end());
}

int H, W, n;
int xl[N + 5], yl[N + 5], xr[N + 5], yr[N + 5];

vector<int> r, d, l, u;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    init();
    scanf("%d%d%d", &H, &W, &n);
    for(int i = 0; i <= n + 1; ++i) scanf("%d%d%d%d", xl + i, yl + i, xr + i, yr + i);

    solve0(d, r, xr[0] - xl[0] + 1, yr[0] - yl[0] + 1);

    for(int i = 1; i <= n + 1; ++i) {
        solve1(d, r, u, l, xl[i]-xr[i-1], yl[i]-yr[i-1], xr[i]-xl[i]+1, yr[i]-yl[i]+1);
        if(i != n+1) solve2(u, l, d, r, xr[i]-xl[i]+1, yr[i]-yl[i]+1);
    }

    reverse(u.begin(), u.end());
    reverse(l.begin(), l.end());

    solve0(d, r, xr[n + 1] - xl[n + 1] + 1, yr[n + 1] - yl[n + 1] + 1);

    int ans = 0;
    for(int i = 0; i < (int) d.size(); ++i) { ans = (ans + (ll) d[i] * u[i]) % mo; }
    for(int i = 0; i < (int) r.size(); ++i) { ans = (ans + (ll) r[i] * l[i]) % mo; }
    printf("%d\n", ans);

    return 0;
}
