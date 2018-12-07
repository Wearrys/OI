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

const int N = 300;

int n, k;
char S[N + 5];
int dp[N + 5][N + 5][N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%s", S + 1);
    read(k), n = strlen(S + 1);

    if(n == 1) return !puts("1");

    for (int i = 1; i <= n; ++ i) dp[i][i][0] = 1, dp[i][i+1][S[i] != S[i+1]] = 2;
    for (int l = 2; l <= n; ++ l) {
        for (int i = 1; i + l - 1 <= n; ++ i) {
            int j = i + l - 1;

            for (int t = 0; t <= k; ++ t) {
                chkmax(dp[i][j][t], dp[i+1][j][t]);
                chkmax(dp[i][j][t], dp[i][j-1][t]);

                if(i<j-1) 
                    chkmax(dp[i][j][t], dp[i+1][j-1][t] + (S[i] == S[j]) *2);
                if(t) 
                    chkmax(dp[i][j][t], dp[i+1][j-1][t-1] + 2);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= k; ++ i) {
        chkmax(ans, dp[1][n][i]);
    }
    printf("%d\n", ans);

    return 0;
}
