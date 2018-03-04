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

const int N = 100;
const int mo = 1e9 + 7;

int n, m;
int binom[N + 5][N + 5];
int dp[N + 5][N + 5][N + 5];

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = 1ll * res * x % mo;
        x = 1ll * x * x %mo;
    }
    return res;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int t, p;
    read(t), read(p);

    for (int i = 0; i <= N; ++i) {
        binom[i][0] = binom[i][i] = 1;
        for (int j = 1; j < i; ++j) binom[i][j] = (binom[i-1][j] + binom[i-1][j-1]) % mo;
    }

    while(t--) {
        read(n), read(m);
        memset(dp, 0, sizeof dp);

        int ans = 0;
        dp[0][0][0] = 1;
        for (int i = 0; i <= n + m; ++i) {
            for (int j = 0; j <= n; ++j) {
                for (int k = 0; k <= i; ++k) {
                    if(j < n) 
                        (dp[i+1][j+1][k+1] += dp[i][j][k]) %= mo;
                    (dp[i+1][j][std::max(k - 1, 0)] += dp[i][j][k]) %= mo;
                }
            }

            if(i == n + m) {
                for(int j = 0; j <= i; ++j) {
                    ans = (ans + 1ll * dp[i][n][j] * j % mo) % mo;
                }
            }
        }
        ans = 1ll * ans * fpm(binom[n + m][n], mo - 2) % mo;
        printf("%d\n", ans);
    }

    return 0;
}
