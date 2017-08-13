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
 
const LL OO = 0x3f3f3f3f3f3f3f3fLL;
const LL MAX_CNT = LL(1e18);

const int oo = 0x3f3f3f3f;
const int maxn = 100 + 10;
const int maxm = 10000 + 10;

template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int n, m;
int st[maxn], to[maxm], nxt[maxm], w[maxm], s[maxm], e = 1;
void addedge(int u, int v, int wi, int si) {
    to[++e] = v; nxt[e] = st[u]; st[u] = e; w[e] = wi; s[e] = si;
}

LL f[maxn][maxn][maxn << 1];
void bellman_ford() {
    memset(f, oo, sizeof f);

    f[0][0][n] = 1;

    REP(i, 0, n + 1) {
        REP(j, 0, n) REP(k, n-i, n+i+1) if(f[i][j][k] < OO) {
            chkmin(f[i+1][j][k], f[i][j][k]);
            for(int t = st[j]; t; t = nxt[t]) 
                chkmin(f[i+1][to[t]][k + s[t]], f[i][j][k] + w[t]);         
        }
    }
}

vector<int> bak[maxn];
vector<pair<LL, LL> > lim[maxn], all;

LL ceil(LL a, LL b);
LL floor(LL a, LL b);

inline LL floor(LL a, LL b) {
    if(a < 0) a = -a, b = -b;
    if(b < 0) return -ceil(a, -b);
    return a / b;
}
inline LL ceil(LL a, LL b) {
    if(a < 0) a = -a, b = -b;
    if(b < 0) return -floor(a, -b);
    return (a - 1) / b + 1;
}

void calc() {
    REP(i, 0, n) REP(j, 0, 2*n+1) if(f[n][i][j] < OO) {
        LL u = -OO, v = OO;

        REP(k, 0, 2*n+1) if(f[n-1][i][k] < OO) {
            if(k == j) { if(f[n-1][i][k] <= f[n][i][j]) v = u; }
            else {
                LL p = j - k, q = f[n-1][i][k] - f[n][i][j];
                if(p < 0) 
                    chkmax(u, floor(q, p) + 1);
                else 
                    chkmin(v, ceil(q, p));
            }
        }
        if(u < v) lim[i].pb(make_pair(u, v));
    }
}

int vis[maxn], now;
void back(int u) { 
    if(vis[u] == now) return; 
    
    vis[u] = now;
    for(const auto& v : bak[u]) back(v);
}

void get_ans() {

    REP(i, 0, n) {
        ++ now;
        back(i);

        all.clear();
        REP(j, 0, n) if(vis[j] == now) {
            copy(lim[j].begin(), lim[j].end(), back_inserter(all));
        }

        sort(all.begin(), all.end());

        LL lst = -OO, sum = 0;
        for(const auto& x : all) {
            if(x.fst > lst) sum += x.fst - lst;
            chkmax(lst, x.snd);
        }

        sum += OO - lst;
        
        printf("%lld\n", sum > MAX_CNT ? -1 : sum);
    }
}

int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    scanf("%d%d", &n, &m);
    REP(i, 0, m) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        -- a, -- b;
        addedge(a, b, c, d); bak[b].pb(a); 
    }

    bellman_ford();

    calc();

    get_ans();

    return 0;
}

