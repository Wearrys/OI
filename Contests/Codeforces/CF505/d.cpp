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

const int N = 700;

int n;
int a[N + 5];
bool can[N + 5][N + 5];
int dp[N + 5][N + 5][2];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    for(int i = 1; i <= n; ++i) scanf("%d", a + i), dp[i][i][0] = dp[i][i][1] = 1;
    for(int i = 1; i <= n; ++i) 
        for(int j = 1; j <= n; ++j) if(std::__gcd(a[i], a[j]) > 1) can[i][j] = true;

    for(int l = 1; l <= n; ++l) {
        for(int i = 1; i + l - 1 <= n; ++i) {
            int j = i + l - 1;

            for(int k = i; k <= j; ++k) {
                if(dp[i][k][1] && dp[k][j][0]) {
                    if(i > 0 && can[k][i-1]) dp[i-1][j][0] |= 1;
                    if(j < n && can[k][j+1]) dp[i][j+1][1] |= 1;
                }
            }
        }
    }
    bool res = 0;
    for(int i = 1; i <= n; ++i) {
        if(dp[1][i][1] && dp[i][n][0]) res = 1;
    }
    puts(res ? "Yes" : "No");

    return 0;
}

