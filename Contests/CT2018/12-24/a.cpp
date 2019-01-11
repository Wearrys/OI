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

const int N = 1 << 18;
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
    void init(int m) {
        n = m + 1;  
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
                    int u = (ll) x[i + j];
                    int v = (ll) x[i + l + j] * w % mo;

                    w = (ll) w * wn % mo;
                    x[i + j] = (u + v) % mo;
                    x[i + l + j] = (u - v + mo) % mo;
                }
            }
        }

        if(ty == -1) {
            int invn = fpm(n, mo - 2);
            for(int i = 0; i < n; ++i) x[i] = (ll) x[i] * invn % mo;
        }
    }

    void mul(int *x, int *y, int *r, int a, int b) {
        init(a + b);
        static int tx[N + 5], ty[N + 5];
        for(int i = 0; i < n; ++i) {
            tx[i] = (i < a ? x[i] : 0);
            ty[i] = (i < b ? y[i] : 0);
        }
        dft(tx, +1), dft(ty, +1);
        for(int i = 0; i < n; ++i) tx[i] = (ll) tx[i] * ty[i] % mo;
        dft(tx, -1);
        for(int i = 0; i < n; ++i) r[i] = tx[i];
    }
}

int fac[N + 5], inv[N + 5];
inline int binom(int n, int k) {
    return (ll) fac[n] * inv[k] % mo * inv[n-k] % mo;
}

void init() {
    fac[0] = 1;
    for(int i = 1; i <= N; ++i) fac[i] = (ll) fac[i-1] * i % mo;
    inv[N] = fpm(fac[N], mo - 2);
    for(int i = N; i >= 1; --i) inv[i-1] = (ll) inv[i] * i % mo;
}

int n, k, ans;
int f[N + 5], g[N + 5];

int calc(int m) {
    int invm = fpm(m, mo - 2);
    int res = 0, t = fpm(invm, k);

    for(int p = k; p <= m * (k - 1) + 1; ++ p) {
        res = (res + (ll) p * t % mo * m % mo * binom(p-1, k-1) % mo * fac[p-k] % mo * g[p-k]) % mo;
        t = (ll) t * invm % mo;
    }
    return res;
}

int main() {
   
    init();
    read(n), read(k); g[0] = 1;
    for(int i = 0; i < k; ++i) f[i] = inv[i];
    for(int i = 1; i <= n; ++i) {
        ans = (ans + (ll) ((i & 1) ? binom(n, i) : mo - binom(n, i)) * calc(i) % mo * fpm(i, mo - 2)) % mo;
        Poly::mul(g, f, g, (i-1) * (k-1) + 1, k);
    }
    printf("%lld\n", (ll) ans * n % mo);

    return 0;
}
