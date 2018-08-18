#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb push_back
#define eb emplace_back
#define REP(i, a, b)  for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i=(a-1), i##end = (b); i >=i##end; --i)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const int oo = 0x3f3f3f3f;
const int maxn = 2000 + 10;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}
 
int n, m;
int cnt[maxn][maxn][2];
char st[maxn][maxn];
 
int fa[maxn], sz[maxn];
int findset(int u) {
    return (u == fa[u]) ? u : fa[u] = findset(fa[u]);
}
int merge(int u, int v) {
    u = findset(u);
    v = findset(v);
    fa[u] = v;
    return sz[v] += sz[u];
}
 
int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif
 
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) { scanf("%s", st[i]); }
    for(int i = 0; i<n-1; ++i) {
        for(int j = m-1; j >= 0; --j) {
            if(st[i][j] == st[i+1][j]) {
                cnt[i][j][0] = cnt[i][j+1][0] + 1;
            }else {
                cnt[i][j][1] = cnt[i][j+1][1] + 1;
            }
        }
    }
 
    int ans = max(n, m);
    for(int i = 0; i < m; ++i) {
        static pii tmp[maxn];
        for(int j = 0; j<n-1; ++j) {
            fa[j] = j;
            sz[j] = 1;
            tmp[j] = pii(cnt[j][i][0] ? cnt[j][i][0] : cnt[j][i][1], j);
        }
        sz[n-1] = 1;
        fa[n-1] = n-1;
 
        sort(tmp, tmp + n-1, greater<pii>());
 
        for(int j = 0; j < n-1; ++j) {
            int p = tmp[j].snd; 
            chkmax(ans, tmp[j].fst * merge(p, p + 1));
        }
    }
    printf("%d\n", ans);
 
    return 0;
}
