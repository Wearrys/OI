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

const int N = 50;
const ll OO = 0x3f3f3f3f3f3f3f3fll;

int n, m, d;
int p[N + 5];

struct item {
    ll val;
    int lim, sz;

    bool operator < (const item& rhs) const {
        return val * rhs.sz < rhs.val * sz;
    }
};

item it[N + 5];
int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n); read(m), read(d);

    read(it[1].val);
    for(int i = 2; i <= n; ++i) read(it[i].val), read(p[i]);
    for(int i = n; i >= 1; --i) {
        it[i].sz ++;
        it[p[i]].sz += it[i].sz;
        it[p[i]].val += it[i].val;
        it[i].lim = (i == 1 ? oo : d);
    }
    std::sort(it + 1, it + n + 1);

    static ll dp[N * N * N + 5];
    for(int i = 0; i <= N*N*N; ++i) dp[i] = OO;

    dp[0] = 0;
    for(int i = 1; i <= n; ++i) {
        int t = std::min(n, it[i].lim);
        it[i].lim -= t;

        for(int j = 1; j <= t; j <<= 1) {
            for(int k = n*n*n; k >= j * it[i].sz; --k)
                chkmin(dp[k], dp[k - j * it[i].sz] + j * it[i].val);
            t -= j;
        }
        if(t) {
            for(int k = n*n*n; k >= t * it[i].sz; --k)
                chkmin(dp[k], dp[k - t * it[i].sz] + t * it[i].val);
        }
    }

    ll ans = 0;
    for(int i = 0; i <= n*n*n; ++i) if(dp[i] <= m) {
        ll res = i, w = m - dp[i];

        for(int j = 1; j <= n; ++j) {
            ll tmp = std::min((ll) it[j].lim, w / it[j].val);

            w -= tmp * it[j].val;
            res += tmp * it[j].sz;
        }

        chkmax(ans, res);
    }
    printf("%lld\n", ans);

    return 0;
}
