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

const int N = 100000;
const int S = 1 << 16;

int n;
int val[N + 5];
bool can[S + 5];
int dp[S + 5], cnt[16];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d", &n);
    for(int i = 1; i < n; ++i) {
        static int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        val[u] ^= w;
        val[v] ^= w;
    }

    for(int i = 1; i <= n; ++i) {
        ++ cnt[val[i]];
    }

    int ans = 0, mask = 0;
    for(int i = 1; i < 16; ++i) {
        ans += cnt[i] / 2;
        if(cnt[i] &= 1) mask |= 1 << i;
    }

    for(int i = 0; i < S; ++i) {
        int res = 0;
        for(int j = 0; j < 16; ++j) if(i >> j & 1) res ^= j;
        if(res == 0) can[i] = true;
    }

    for(int i = 0; i < S; ++i) {
        for(int j = i; j; j = (j - 1) & i) 
            if(can[j]) { chkmax(dp[i], dp[i ^ j] + 1); }
    }

    printf("%d\n", ans + __builtin_popcount(mask) - dp[mask]);

    return 0;
}
