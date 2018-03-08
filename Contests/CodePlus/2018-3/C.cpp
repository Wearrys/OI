#include <bits/stdc++.h>

using std::pair;
using std::vector;
using std::string;

typedef long long ll;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back
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

const int B = 500;
const int N = 500000;
const int mo = 1e9 + 7;

int fac[N + 5], inv[N + 5];
int binom(int n, int k) {
    if(n < k || n < 0 || k < 0) return 0;
    return 1ll * fac[n] * inv[k] % mo * inv[n - k] % mo;
}

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = 1ll * res * x % mo;
        x = 1ll * x * x % mo;
    }
    return res;
}

int f[N / B + 5];
int query(int n, int m) {
    if(!n) return 0;

    int ans = f[(n - 1) / B];
    for(int i = (n - 1) / B * B + 1; i < n; ++i) {
        ans = (ans + binom(m, i)) % mo;
    }
    return ans;
}

void init() {
    fac[0] = 1;
    for(int i = 1; i <= N; ++i) fac[i] = 1ll * fac[i-1] * i % mo;
    inv[N] = fpm(fac[N], mo - 2);
    for(int i = N; i >= 1; --i) inv[i-1] = 1ll * inv[i] * i % mo;
}

int ans[N + 5];
struct node { int d, n, m, id; };
vector<node> que[N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int T, n, m, p;
    init();
    read(T), read(p);

    for(int i = 0; i < T; ++i) { 
        read(n), read(m);
        if(n >= m) {
            que[n + m].pb((node){ n-m, m, n, i });
        } else {
            que[n + m].pb((node){ 0, n, m, i });
        }
    }

    int pw = 1;
    for(int i = 0; i <= N; ++i) {
        if(i % B == 0) { f[i / B] = pw; }
        for(int j = 0; j*B < i; ++j) 
            f[j] = (2ll*f[j] - binom(i-1, j*B) + mo) % mo;
        pw = (pw << 1) % mo;

        for(auto q : que[i]) {
            ans[q.id] = (q.d + 1ll*fpm(binom(i, q.n), mo-2) * query(q.n, i)) % mo;
        }
    }
    for(int i = 0; i < T; ++i) printf("%d\n", ans[i]);

    return 0;
}
