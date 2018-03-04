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

const int N = 500000;
const int mo = 998244353;

int fpm(int x, int y) {
    int res = 1;
    for (; y > 0; y >>= 1) {
        if(y & 1)
            res = 1ll * res * x % mo;
        x = 1ll * x * x % mo;
    }
    return res;
}

int fac[N + 5], inv[N + 5];

inline int binom(int n, int k) {
    if(n < 0 || k < 0 || n < k) return 0;
    return 1ll * fac[n] * inv[k] % mo * inv[n-k] % mo;
}

inline int calc(int x, int y, int t) {
    return (binom(x + y, x) - binom(x + y, y - t) + mo) % mo;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i <= N; ++i) fac[i] = 1ll * fac[i-1] * i % mo;
    inv[N] = fpm(fac[N], mo - 2);
    for (int i = N; i >= 1; --i) inv[i-1] = 1ll * inv[i] * i % mo;
}

int n, k;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    init();
    read(n), read(k);

    int ans = 0;
    for(int r = k; r * 2 >= k && r >= n; --r) {
        int b = k - r, t = r - n + 1;
        if(r == b) -- b;
        ans = (ans + calc(r, b, t)) % mo;
    }
    printf("%d\n", ans);

    return 0;
}
