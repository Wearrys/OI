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

template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

const int N = 400;
const int mo = 998244353;

inline void add(int &x, int y) {
    if((x += y) >= mo) x -= mo;
}

int dp[N + 5][N + 5], n, k;
int pw[N + 5][N + 5], w[N + 5];

int main() {
#ifdef Wearry
    freopen("data", "r", stdin);
    freopen("ans", "w", stdout);
#endif

    read(n), read(k);

    pw[0][0] = 1;
    for(int i = 1; i <= n; ++i) {
        read(w[i]);

        pw[i][0] = 1;
        for(int j = 1; j <= n; ++j) 
            pw[i][j] = 1ll * pw[i][j-1] * i % mo; 
    }

    for(int i = 1; i <= k; ++i) 
        for(int j = 1; j <= n; ++j) dp[i][j] = 1ll * pw[j][i-1] * w[j] % mo;

    for(int i = 2; i <= n - k + 1; ++i) {

        int temp = 0;
        for(int t = 1; t <= n; ++ t) {
            for(int j = i-1; j < i+k-1; ++j) {
                temp = (temp + 1ll * dp[j][t] * pw[t-1][i+k-2-j]) % mo;
            }
            add(dp[i+k-1][t], temp);
        }

        for(int j = i; j <= i+k-1; ++j) {
            temp = 0;
            for(int t = n; t >= 1; -- t) {
                dp[j][t] = (dp[j][t] + 1ll * temp * pw[t][j-i]) % mo;         
                add(temp, dp[i-1][t]);
            }
        }

        for(int j = i; j <= i+k-1; ++j)
            for(int t = 1; t <= n; ++t) dp[j][t] = 1ll * dp[j][t] * w[t] % mo;
    }

    int res = 0;
    for(int i = n-k+1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            res = (res + 1ll * dp[i][j] * pw[j-1][n-i]) % mo;
        }
    }
    printf("%d\n", res);

    return 0;
}
