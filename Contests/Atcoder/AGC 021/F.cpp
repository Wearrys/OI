#include <bits/stdc++.h>

using std::pair;
using std::vector;
using std::string;

typedef long long ll;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb(a) push_back(a)
#define mp(a, b) std::make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)

template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;

string procStatus() {
    std::ifstream t("/proc/self/status");
    return string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}

template <typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int M = 200;
const int N = 8005;
const int mo = 998244353;

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
    inline void init(int len) {
        n = len;
        while(n != (n & -n)) n += (n & -n);
    }

    void dft(int *x, int ty) {
        for(int i = 0, j = 0; i < n; ++i) {
            if(i < j) std::swap(x[i], x[j]);
            for(int l = n >> 1; (j ^= l) < l; l >>= 1);
        }

        for(int l = 1; l < n; l <<= 1) {
            int wn = fpm(g, (mo - 1) / 2 / l);
            if(ty == -1) wn = fpm(wn, mo - 2);

            for(int i = 0; i < n; i += (l << 1)) {
                int w = 1, *u = x + i, *v = x + i + l;
                for(int j = 0; j < l; ++j) {
                    int t0 = (*u + (ll) *v * w) % mo;
                    int t1 = (*u - (ll) *v * w) % mo;

                    *u = t0, *v = t1;
                    w = (ll) w * wn % mo;
                    ++ u, ++ v;
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
}

int n, m;
int f[N + 5][M + 5];
int fac[N + 5], inv[N + 5];

void init() {
    fac[0] = 1;
    for(int i = 1; i <= N; ++i) fac[i] = (ll) fac[i-1] * i % mo;
    inv[N] = fpm(fac[N], mo - 2);
    for(int i = N; i >= 1; --i) inv[i-1] = (ll) inv[i] * i % mo;
}

inline int binom(int x, int y) {
    if(x < 0 || y < 0 || x < y) return 0;
    return (ll) fac[x] * inv[y] % mo * inv[x-y] % mo;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    init();
    read(n), read(m); 

    f[0][0] = 1;
    Poly::init(2*n + 3);

    static int tx[(N<<2) + 5], ty[(N<<2) + 5];

    for(int j = 1; j <= m; ++j) {
        for(int i = 0; i < Poly::n; ++i) tx[i] = i <= n ? (ll) f[i][j-1] * inv[i] % mo : 0;
        for(int i = 0; i < Poly::n; ++i) ty[i] = (3 <= i && i <= n + 2) ? inv[i] : 0;

        Poly::dft(tx, +1);
        Poly::dft(ty, +1);

        for(int i = 0; i < Poly::n; ++i) tx[i] = (ll) tx[i] * ty[i] % mo;

        Poly::dft(tx, -1);

        for(int i = 0; i <= n; ++i) {
            f[i][j] = (f[i][j] + (ll) (binom(i + 1, 2) + 1) * f[i][j-1]) % mo;
            f[i][j] = (f[i][j] + (ll) tx[i + 2] * fac[i + 2]) % mo;
        }
    }

    int ans = 0;
    for(int i = 0; i <= n; ++i) {
        ans = (ans + (ll) binom(n, i) * f[i][m]) % mo;
    }
    printf("%d\n", (ans + mo) % mo);

    return 0;
}
