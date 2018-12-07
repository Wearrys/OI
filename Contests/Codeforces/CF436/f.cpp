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
const int maxn = 3000 + 5;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int n, m, q;
vector<int> G[maxn];
bool can[maxn][maxn];
unsigned short to[maxn][maxn][13];

void Input() {
    n = read<int>();
    m = read<int>();
    q = read<int>();

    for(int i = 1; i <= m; ++i) {
        static int x, y;
        x = read<int>(); 
        y = read<int>(); G[x].pb(y);
    }
}

int rt;
void dfs(int u) {
    if(can[rt][u]) return;
    can[rt][u] = true;

    for(const auto& v : G[u]) { dfs(v); }
}

void Init() {
    for(int i = 1; i <= n; ++ i) rt = i, dfs(i); 
    for(int i = 1; i <= n; ++ i) {
        for(const auto& v : G[i]) {
            for(int j = 1; j <= n; ++ j) if(can[v][j] && i != j) {
                if(!to[i][j][0] || v < to[i][j][0]) to[i][j][0] = v; 
            }
        }
    }
    for(int k = 1; k <= 12; ++k) {
        for(int i = 1; i <= n; ++i) 
            for(int j = 1; j <= n; ++j) 
                to[i][j][k] = to[to[i][j][k-1]][j][k-1];
    }
}

int get_ans(int s, int t, int k) {
    //cerr << to[s][t][12] << endl;
    if(can[to[s][t][12]][t]) return 0;
    
    int cur = s;
    for(int i = 12; i >= 0; --i) if(k >> i & 1) {
        cur = to[cur][t][i];
        if(cur == 0) return 0;
    }
    return cur;
}
void Solve() {
    while(q--) {
        static int s, t, k, ans;
        s = read<int>(), t = read<int>(), k = read<int>();
        if(!can[s][t] || !(ans = get_ans(s, t, k - 1))) puts("-1"); else printf("%d\n", ans);
    }
}

int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif 

    Input();
    Init();
    Solve();

    return 0;
}
