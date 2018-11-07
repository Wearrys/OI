#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int mo;
const int M = 1000000;
const int N = 1000005;

int fpm(int x, int y) {
    int res = 1;
    for(x = (x + mo) % mo; y > 0; y >>= 1) {
        if(y & 1)
            res = (ll) res * x % mo;
        x = (ll) x * x % mo;
    }
    return res;
}

int f[N + 5], ans;
int a, b, c, n, m, h;
int fac[N + 5], inv[N + 5], upow[N + 5];

inline int binom(int x, int y) {
    return (ll) fac[x] * inv[y] % mo * inv[x - y] % mo;
}

void init() {
    fac[0] = 1;
    for(int i = 1; i <= N; ++i) fac[i] = (ll) fac[i-1] * i % mo;
    inv[N] = fpm(fac[N], mo - 2);
    for(int i = N; i >= 1; --i) inv[i-1] = (ll) inv[i] * i % mo;

    upow[0] = 1;
    for(int i = 1; i <= N; ++i) upow[i] = (ll) upow[i-1] * (m + i - 1) % mo;
}

void calc_s(int x, int *s) {
    if(x == 1) {
        for(int i = 0; i <= M; ++i) s[i] = (ll) upow[i+1] * inv[i+1] % mo;
    } else {
        const int powm = fpm(x, m), invx = fpm(x - 1, mo - 2);

        s[0] = (ll) (powm - 1 + mo) * invx % mo;
        for(int i = 1; i <= M; ++i) s[i] = ((ll) powm * upow[i] % mo * inv[i] % mo - s[i-1] + mo) * invx % mo;
    }
}

void calc_t(int x, int *s, int *t) {
    calc_s(x, s);
    if(x == 1) {
        for(int i = 0; i <= M; ++i) t[i] = (ll) upow[i+2] * inv[i+2] % mo;
    } else {
        const int invx = fpm(x - 1, mo - 2);
        t[0] = (((ll) x * s[0] % mo - m) % mo + mo) % mo * invx % mo;
        for(int i = 1; i <= M; ++i) t[i] = ((ll) x * s[i] % mo - t[i-1] + mo) * invx % mo;
    }
}

void solve_f() {
    static int s[N + 5];
    calc_s((ll) b * h % mo, s);

    const int powm = fpm(h, m), invh = fpm(powm, mo - 2);

    int sum = 0, temp = 1;
    int curp = (ll) b * fpm(fpm(h, n-1), m) % mo;

    for(int i = 0; i < n; ++i) {
        sum = (sum + (ll) temp * s[i]) % mo;
        ans = (ans + (ll) sum * curp % mo * f[n - i]) % mo;
        temp = (ll) temp * powm % mo * a % mo;
        curp = (ll) curp * invh % mo;
    }
}

void solve_c() {
    static int s[N + 5], t[N + 5];

    if(h != 1) {
        calc_s(b, s);
        calc_s((ll) b * h % mo, t);

        const int powm = fpm(h, m), invh = fpm(powm, mo - 2), inva = fpm(a, mo - 2), _invh = fpm(h - 1, mo - 2);

        int curp = fpm(fpm(h, n-1), m);
        int sum = 0, temp = (ll) c * fpm(a, n - 1) % mo;

        for(int i = 0; i < n; ++i) {
            sum = (sum + curp) % mo;
            ans = (ans + (ll) temp * sum % mo * _invh % mo * ((ll) powm * s[n - 1 - i] % mo - t[n - 1 - i] + mo)) % mo;
            temp = (ll) temp * inva % mo;
            curp = (ll) curp * invh % mo;
        }
    } else {
        calc_t(b, s, t);

        const int powm = fpm(h, m), invh = fpm(powm, mo - 2), inva = fpm(a, mo - 2);

        int curp = fpm(fpm(h, n-1), m);
        int sum = 0, temp = (ll) c * fpm(a, n - 1) % mo;

        for(int i = 0; i < n; ++i) {
            sum = (sum + curp) % mo;
            ans = (ans + (ll) temp * sum % mo * t[n - 1 - i]) % mo;
            temp = (ll) temp * inva % mo;
            curp = (ll) curp * invh % mo;
        }
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%*d%d%d", &n, &m);
    scanf("%d%d%d%d%d", &h, &mo, &a, &b, &c);
    for(int i = 1; i <= n; ++i) scanf("%d", f + i);

    init();
    solve_f();
    solve_c();

    printf("%d\n", ans);

    return 0;
}
