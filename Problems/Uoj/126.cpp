#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb push_back
#define eb emplace_back
#define REP(i, a, b)  for(LL i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(LL i=(a-1), i##end = (b); i >=i##end; --i)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const int mod = 1e9 + 7;
const int oo = 0x3f3f3f3f;
const int maxn = 100000 + 10; 
const int maxm = 200000 + 10;
 
template<typename T> T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}
 
LL ans, f[maxn];
int n, ind[maxn];
int st[maxn], to[maxm], nxt[maxm], w[maxm], e = 1;

void addedge(int x, int y, int z) {
    ++ ind[x], ++ ind[y];
    to[++e] = y; nxt[e] = st[x]; st[x] = e; w[e] = z;
    to[++e] = x; nxt[e] = st[y]; st[y] = e; w[e] = z;
}

LL pre[2][maxn], suf[2][maxn];
void calc(pair<int, LL>* stk, int top, LL len, LL wi) {

    LL ret = 1LL << 60, tmp = 0;

    REP(i, 0, top) {
        pre[0][i] = max(i?pre[0][i-1]:-1, stk[i].snd + f[stk[i].fst]);
        pre[1][i] = max(i?pre[1][i-1]:-1, stk[i].snd + f[stk[i].fst] + tmp);
        chkmax(tmp, f[stk[i].fst] - stk[i].snd);
    }

    tmp = 0;
    DREP(i, top, 0) {
        suf[0][i] = max(suf[0][i+1], len - stk[i].snd + f[stk[i].fst]);
        suf[1][i] = max(suf[1][i+1], len - stk[i].snd + f[stk[i].fst] + tmp);
        chkmax(tmp, f[stk[i].fst] - len + stk[i].snd);
    }

    ret = pre[1][top-1];
    REP(i, 0, top-1) {
        ret = min(ret, max(max(pre[1][i], suf[1][i+1]), pre[0][i] + suf[0][i+1] + wi));
    }
    chkmax(ans, ret);
}

void dfs(int u, int fa = 0) {
    for(int i = st[u]; i; i = nxt[i]) {
        if(ind[to[i]] != 2 && to[i] != fa) {
            dfs(to[i], u);
            chkmax(ans, f[to[i]] + f[u] + w[i]);
            chkmax(f[u], f[to[i]] + w[i]);
        }
    }
}

void solve() {

    static int q[maxn];
    int head = 0, tail = 0, top = 0;
    static pair<int, LL> stk[maxn << 1];

    for(int i = 1; i <= n; i++) if(ind[i] == 1) q[tail++] = i;
    while(head < tail) {
        int x = q[head++];
        for(int i = st[x]; i; i = nxt[i]) if(--ind[to[i]] == 1) q[tail++] = to[i];
    }

    static bool vis[maxn];
    LL len = head = tail = 0, wi = -1;
    for(int i = 1; i <= n; i++) if(ind[i] == 2) dfs(i);
    for(int i = n; i >= 1; i--) if(ind[i] == 2) { vis[q[tail++] = i] = 1; break; }

    while(head < tail) {
        int x = q[head++]; 
        stk[top++] = make_pair(x, len);

        for(int i = st[x]; i; i = nxt[i]) 
            if(ind[to[i]] == 2 && !vis[to[i]]) {
                len += w[i]; vis[to[i]] = 1; q[tail++] = to[i];
                break;
            }
        if(head == 1) for(int i = st[x]; i; i = nxt[i]) 
            if(ind[to[i]] == 2 && !vis[to[i]]) wi = w[i]; 
    }
    calc(stk, top, len, wi);
}

int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif
 
    n = read<int>();
    for(LL i = 1; i <= n; i++) { 
        static LL x, y, z;
        x = read<int>();
        y = read<int>();
        z = read<int>();
        addedge(x, y, z);
    }
    solve();
    printf("%lld.%d\n", ans>>1, (ans&1) ? 5 : 0);

    return 0;
}
