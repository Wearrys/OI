#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb push_back
#define REP(i, a, b)  for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i=(a-1), i##end = (b); i >=i##end; --i)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const int oo = 0x3f3f3f3f;
const int maxn = 100000 + 5;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int n, m;
vector<int> G[maxn];
bool col[maxn][2];

int cnt = 0;
bool flag = true;

void dfs(int u, int c = 0) {

    if(c) ++ cnt;
    col[u][c] = true;
    for(const auto&v : G[u]) {
        if(col[v][c]) flag = false;
        if(!col[v][c^1]) dfs(v, c ^ 1);
    }
}

int main() {
#ifdef Wearry
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    n = read<int>();
    m = read<int>();
    for(int i = 0; i < m; ++i) {
        int u = read<int>(), v = read<int>();
        G[u].pb(v), G[v].pb(u);
    }

    dfs(1);

    if(flag) {
        printf("%lld\n", 1LL * (n - cnt) * cnt - m);
    }
    else printf("%lld\n", 1LL * n * (n-1) / 2 - m);

    return 0;
}
