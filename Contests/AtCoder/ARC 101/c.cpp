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

const int N = 5000;
const int mo = 1e9 + 7;

int n;
vector<int> G[N + 5];
int dp[N + 5][N + 5], sz[N + 5], fac[N + 5];

void init() {
    fac[0] = 1;
    for(int i = 1; i <= N; ++i) if(i % 2 == 0) fac[i] = ll(i-1) * fac[i-2] % mo;
}

void add(int &x, int y) {
    (x += y) >= mo ? x -= mo : 0;
}

void dfs(int u, int f = 0) {
    sz[u] = 1;
    dp[u][1] = 1;

    for(auto v : G[u]) if(v != f) {
        dfs(v, u);

        static int tmp[N + 5];
        for(int x = 0; x <= sz[v] + sz[u]; ++x) tmp[x] = 0;
        for(int i = 0; i <= sz[u]; ++i) {
            for(int j = 0; j <= sz[v]; ++j) {
                add(tmp[i + j], (ll) dp[u][i] * dp[v][j] % mo);
            }
        }
        for(int x = 0; x <= sz[v] + sz[u]; ++x) dp[u][x] = tmp[x];
        sz[u] += sz[v];
    }
    for(int i = 2; i <= sz[u]; ++i) {
        add(dp[u][0], mo - ((ll) dp[u][i] * fac[i] % mo));
    }
    
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    init();
    read(n);
    for(int i = 1; i < n; ++i) {
        static int x, y;
        read(x), read(y);
        G[x].pb(y), G[y].pb(x);
    }

    dfs(1);
    printf("%d\n", mo - dp[1][0]);

    return 0;
}
