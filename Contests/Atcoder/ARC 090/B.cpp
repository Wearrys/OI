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
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

const int N = 100000;

int n, m;
ll dis[N + 5];
bool vis[N + 5];
vector<pii> G[N + 5];

bool flag = true;

void dfs(int u, ll d) {

    if(vis[u]) {
        if(dis[u] != d) flag = false;
        return;
    }

    vis[u] = 1;
    dis[u] = d;

    for(int i = 0; i < (int) G[u].size(); ++i) {
        dfs(G[u][i].fst, d + G[u][i].snd);
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif 

    read(n), read(m);
    for(int i = 1; i <= m; ++i) {
        static int l, r, d;
        read(l), read(r), read(d);

        G[r].pb(mp(l, d));
        G[l].pb(mp(r, -d));
    }

    for(int i = 1; i <= n; ++i) if(!vis[i]) {
        dfs(i, 0);
    }
    puts(flag ? "Yes" : "No");

    return 0;
}
