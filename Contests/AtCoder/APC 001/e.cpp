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

int n, f[N + 5];
vector<int> G[N + 5];

void dfs(int u, int fa = -1) {

    int c = 0;
    for(int i = 0; i < (int) G[u].size(); ++i) {
        int v = G[u][i];
        if(v == fa) continue;

        dfs(v, u);

        if(!f[v]) {
            ++ c;
        } else {
            f[u] += f[v];
        }
    }
    if(c) f[u] += c - 1;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    
    read(n);
    for(int i = 1; i < n; ++i) {
        static int u, v;
        read(u), read(v);
        G[u].pb(v), G[v].pb(u);
    }

    for(int i = 0; i < n; ++i) if((int) G[i].size() >= 3) {
        dfs(i);
        printf("%d\n", f[i]);
        return 0;
    }
    printf("1\n");
    return 0;
}
