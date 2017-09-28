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
 
const int N = 40;
const int oo = 0x3f3f3f3f;
const int mod = 998244353;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

LL fpm(LL base, LL exp) {
    LL res = 1;
    for(; exp > 0; exp >>= 1) {
        if(exp & 1) 
            res = res * base % mod;
        base = base * base % mod;
    }
    return res;
}

int n, m;
vector<int> V, G[N + 5];
struct Edge { int u, v, w; } E[N + 5]; 

int col[N + 5], id[N + 5], cnt;

void color(int u) {
    col[u] = cnt;
    id[u] = V.size(); V.pb(u);
    for(const auto& v : G[u]) if(!col[v]) color(v);
}

LL pw[N * N + 5];
LL g[N + 5][N + 5], f[N + 5][N + 5];

void calc() {
    int all = 1 << V.size();
    for(int s = 0; s < all; ++ s) {
        LL res = 1;
        for(int i = 0; i < m; ++i) {
            if(col[E[i].u] == cnt && ((s >> id[E[i].u] & 1) != (s >> id[E[i].v] & 1))) {
                res = (res << 1) * ((s >> id[E[i].u] & 1) ? E[i].w : 1 - E[i].w) % mod;
            }
        }
        (g[cnt][__builtin_popcount(s)] += res) %= mod;
    }
}

int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    pw[0] = 1;
    for(int i = 1; i <= N*N; ++i) pw[i] = pw[i-1] * ((mod + 1) >> 1) % mod;

    n = read<int>();
    m = read<int>();

    for(int i = 0; i < m; ++i) {
        E[i].u = read<int>();
        E[i].v = read<int>();
        E[i].w = read<LL>() * 796898467 % mod;

        G[E[i].u].pb(E[i].v);
        G[E[i].v].pb(E[i].u);
    }

    for(int i = 1; i <= n; ++i) if(!col[i]) {
        ++ cnt;
        V.clear();
        color(i); calc();
    }

    f[0][0] = 1;
    for(int i = 1; i <= cnt; ++i) {
        for(int j = 0; j <= n; ++j)
            for(int k = 0; k <= j; ++k) 
                (f[i][j] += f[i-1][j-k] * g[i][k]) %= mod;
    }

    LL Ans = 0;
    for(int i = 1; i <= n; ++i) {
        Ans = (Ans + f[cnt][i] * pw[i * (n-i)]) % mod;
    }
    Ans = Ans * fpm(10000, n * (n - 1)) % mod;
    printf("%lld\n", (Ans % mod + mod) % mod);

    return 0;
}
