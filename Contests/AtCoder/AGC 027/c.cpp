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

const int N = 400000;

int n, m;
char st[N + 5];
int vis[N + 5];

struct edge {
    int u, v, ty;
};

int e;
edge E[N + 5];
vector<int> G[N + 5][4];

inline void addedge(int u, int v) {
    int ty = -1;
    if(st[u] == 'A') {
        if(st[v] == 'A') ty = 0; else ty = 1;
    } else {
        if(st[v] == 'B') ty = 2; else ty = 3;
    }

    E[++ e] = (edge) { u, v, ty };
    G[u][ty].pb(e);
}

int su, sc;
void dfs(int eid) {
    if(vis[eid] == 2) {
        puts("Yes");
        exit(0);
    }
    if(vis[eid] == 1) {
        return;
    }

    vis[eid] = 2;
    int u = E[eid].v;

    for(auto v : G[u][(E[eid].ty+1)%4]) {
        dfs(v);
    }
    vis[eid] = 1;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(m);
    scanf("%s", st + 1);

    for(int i = 1; i <= m; ++i) {
        static int u, v;
        read(u), read(v);
        addedge(u, v), addedge(v, u);
    }

    for(int i = 1; i <= 2*m; ++i) if(!vis[i]) {
        su = i;
        dfs(i); 
    }
    printf("No\n");

    return 0;
}
