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

const int N = 200000;
const int mo = 998244353;

char st[N + 5];
int dp[N + 5][3][3];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%s", st);

    int s = st[0] - 'a';
    int len = strlen(st), f0 = 1, f1 = 1;

    for(int i = 1; i < len; ++i) {
        f0 &= (st[i] != st[i-1]);
        f1 &= (st[i] == st[i-1]);
        s = (s + st[i] - 'a') % 3;
    }
    if(f1) { return !puts("1"); }
    if(len == 2) return !puts("2");
    if(s == 0 && len == 3) return !puts("3");

    int ans = 1;
    for(int i = 1; i < len; ++i) ans = 3ll * ans % mo;

    for(int i = 0; i < 3; ++i) dp[0][i][i] = 1;
    for(int i = 1; i < len; ++i) {
        for(int j = 0; j < 3; ++j) {
            for(int k = 0; k < 3; ++k) if(dp[i-1][j][k]) {
                for(int l = 0; l < 3; ++l) if(l != j) {
                    (dp[i][l][(k + l) % 3] += dp[i-1][j][k]) %= mo;
                }
            }
        }
    }

    ans = ans + f0;
    for(int i = 0; i < 3; ++i) ans = (ans - dp[len-1][i][s]) % mo;

    printf("%d\n", (ans + mo) % mo);

    return 0;
}
