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

inline int idx(char c) {
    if(c == 'R') return 0;
    else if(c == 'G') return 1;
    else if(c == 'B') return 2;
    else return -1;
}

const int N = 500000;

int n;
char s[N + 5];

inline bool chk(int a, int b, int x, int y) {
    if(a == b) {
        return x != a && y != a;
    } 
    return x != a && x != b;
}

bool dp[N + 5][3][3];
int a[N + 5], b[N + 5], sa[N + 5], sb[N + 5];

inline int solve(int l, int r) {

    dp[l][a[l]][b[l]]= 1;

    int t;
    for(int i = l; i < r; ++i) {
        for(int j = 0; j < 3; ++j) {
            for(int k = 0; k < 3; ++k) if(dp[i][j][k]) {
                t = (a[i + 1] + j - k + 3) % 3;
                if(chk(j, a[i+1], k, t)) dp[i+1][t][b[i+1]] = 1;

                t = (b[i + 1] - j + k + 3) % 3; 
                if(chk(j, t, k, b[i+1])) dp[i+1][a[i+1]][t] = 1;
            }
        }
    }
    
    return (dp[r][0][0] || dp[r][1][1] || dp[r][2][2]) ? r-l : r-l+1;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    scanf("%s", s + 1); 
    for(int i = 1; i <= n; ++i) a[i] = idx(s[i]), sa[i] = (sa[i-1] + a[i]) % 3;
    scanf("%s", s + 1); 
    for(int i = 1; i <= n; ++i) b[i] = idx(s[i]), sb[i] = (sb[i-1] + b[i]) % 3;

    int lst = 1, ans = 0;
    for(int i = 1; i <= n; ++i) if(sb[i] == sa[i]) {
        ans += solve(lst, i), lst = i + 1;
    }

    printf("%d\n", ans);

    return 0;
}
