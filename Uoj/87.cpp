#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> pii;

const LL maxn = 6e5 + 10;
const LL oo = 0x3f3f3f3f;

template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

#define fst first
#define snd second
#define pb push_back
#define debug(x) cerr << #x <<":" << (x) << endl
#define REP(i, a, b) for(LL i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(LL i = (a)-1, i##bgn = (b); i >= i##bgn; --i)

template<typename T> T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48;
	return n * f;
}

LL n, m, q;
namespace tree {
    const LL maxn = 6e5 + 10;

    LL N;
    LL d[maxn], Cd[maxn];
    vector<pii> G[maxn];
//  LL st[maxn], to[maxn<<1], nxt[maxn<<1], w[maxn<<1], ecnt = 1;

    void init() { N = n; }
    void addedge(LL u, LL v, LL wi) {
//      to[++ecnt] = v; nxt[ecnt] = st[u]; st[u] = ecnt; w[ecnt] = wi;
//      to[++ecnt] = u; nxt[ecnt] = st[v]; st[v] = ecnt; w[ecnt] = wi;
        G[u].pb(pii(v, wi));
        G[v].pb(pii(u, wi));
    }

    LL dis[maxn];
    LL fa[maxn][20], dep[maxn], dfn[maxn], dfs_clock;

    LL Lca(LL x, LL y) {
        if(dep[x] < dep[y]) swap(x, y);

        for(LL i = 0, l = dep[x] - dep[y]; i < 20; i++) 
            if(l >> i & 1) x = fa[x][i];
        if(x == y) return x;

        for(LL i = 19; i >= 0; i--) 
            if(fa[x][i] != fa[y][i]) 
                x = fa[x][i], y = fa[y][i];
        return fa[x][0];
    }
    LL getdis(LL x, LL y) {
        LL r = Lca(x, y);
        return dis[x] + dis[y] - 2 * dis[r];
    }
    LL up(LL u, LL de) {
        static LL k;
        k = dep[u] - de - 1;
        for(LL i = 0; k > 0; k >>= 1, i ++) 
            if(k & 1) u = fa[u][i];
        return u;
    }
    void dfs(LL u, LL f = 0) {
        //cerr << u << endl;
        fa[u][0] = f;
        dfn[u] = ++dfs_clock;

        for(LL i = 1; i < 20; i++) 
            fa[u][i] = fa[fa[u][i-1]][i-1];

        for(LL i = 0, v; i < int(G[u].size()); i++) if((v = G[u][i].fst) ^ f) {
            dep[v] = dep[u] + 1;
            dis[v] = dis[u] + G[u][i].snd;
            dfs(v, u);
        }
    }
}

namespace cactus {
    LL st[maxn], to[maxn<<2], nxt[maxn<<2], w[maxn<<2], ecnt = 1;

    void addedge(LL u, LL v, LL wi) {
        to[++ecnt] = v; nxt[ecnt] = st[u]; st[u] = ecnt; w[ecnt] = wi;
        to[++ecnt] = u; nxt[ecnt] = st[v]; st[v] = ecnt; w[ecnt] = wi;
    }

    LL pre[maxn], dfn[maxn], low[maxn], dfs_clock;

    void Solve_Cir(LL u, LL v, LL e) {
        static pii C[maxn];
        static LL cnt; cnt = 0;
        
        C[cnt++] = pii(e, v);
        while(u ^ v) C[cnt++] = pii(pre[v], to[pre[v]]), v = to[pre[v]];

        LL sum = 0;
        for(LL i = 0; i < cnt; i++) 
            tree :: d[C[i].snd] = (sum += w[C[i].fst]);

        ++ tree :: N;
        for(LL i = 0; i < cnt; i++) {
            tree :: Cd[C[i].snd] = sum;
            LL d = tree :: d[C[i].snd];
            tree :: addedge(tree :: N, C[i].snd, min(d, sum-d));
        }
    }

    void dfs(LL u, LL fe = 0) {
        dfn[u] = low[u] = ++dfs_clock; 

        for(LL i = st[u], v; i; i = nxt[i]) if(i ^ fe) {
            v = to[i];
            if(!dfn[v]) {
                dfs(v, pre[v] = i^1);
                if(low[v] > dfn[u]) 
                    tree :: addedge(u, v, w[i]);
                low[u] = min(low[u], low[v]);
            }else if(dfn[v] < low[u]) low[u] = dfn[v];
        }
        for(LL i = st[u], v; i; i = nxt[i]) if(i ^ fe) {
            v = to[i];
            if((i^1) != pre[v] && low[v] == dfn[u]) Solve_Cir(u, v, i);
        }
    }
}

bool cmp(const LL& a, const LL& b) {
    return tree :: dfn[a] < tree :: dfn[b];
}
bool cmp1(const pii& a, const pii& b) {
    return tree :: d[a.fst] < tree :: d[b.fst];
}

namespace Vtree {
    const LL maxn = 6e5 + 10;
    LL w[maxn];
    LL st[maxn], to[maxn], nxt[maxn], ecnt = 1;

    void addedge(LL u, LL v) {
        LL wi = tree :: getdis(u, v);
        to[++ecnt] = v; nxt[ecnt] = st[u]; st[u] = ecnt; w[ecnt] = wi;
        //to[++ecnt] = u; nxt[ecnt] = st[v]; st[v] = ecnt; w[ecnt] = wi;
    }

    LL dp[maxn], len[maxn], ans;
    void dfs(LL u) {
        for(LL i = st[u]; i; i = nxt[i]) 
            dfs(to[i]);

        if(u <= n) {
            for(LL i = st[u], v; i; i = nxt[i]) {
                v = to[i];
                chkmax(ans, dp[u] + dp[v] + w[i]);
                chkmax(dp[u], dp[v] + w[i]);
            }
        }else {
            static LL q[maxn];
            static pii C[maxn];
            static LL cnt, head, tail;

            cnt = head = tail = 0;

            for(LL i = st[u], v; i; i = nxt[i]) {
                v = to[i];
                chkmax(dp[u], dp[v] + w[i]);

                C[cnt++].fst = tree::up(v, tree::dep[u]);
                C[cnt-1].snd = dp[v] + tree::dis[v] - tree::dis[C[cnt-1].fst];
            }

            sort(C, C + cnt, cmp1);

            LL Cirl = tree :: Cd[C[0].fst];
            for(LL i = 0; i < cnt; i++) {
                len[i] = tree::d[C[i].fst];
                len[i+cnt] = len[i] + Cirl; C[i+cnt] = C[i];
            }

            for(LL i = 0; i < 2*cnt; i++) {
                while(head < tail && len[i] - len[q[head]] > Cirl / 2)
                    ++head;
                if(head < tail)
                    chkmax(ans, C[q[head]].snd + C[i].snd + len[i] - len[q[head]]);

                while(head < tail && C[i].snd > C[q[tail-1]].snd + len[i] - len[q[tail-1]])
                    --tail;
                q[tail++] = i;
            }
        }
    }
    LL tot, rt;
    void build(LL *V, LL k) {
        static LL stk[maxn], top;

        sort(V, V + k, cmp);
        tot = k = unique(V, V + k) - V;

        rt = top = 0;
        stk[top++] = 0;
        for(LL i = 0; i < k; i++) {
            LL r = tree :: Lca(V[i], stk[top-1]);

            if(r == stk[top-1]) stk[top++] = V[i];
            else {
                while(top >= 2 && tree::dep[stk[top-2]] >= tree::dep[r]) 
                    addedge(stk[top-2], stk[top-1]), --top;

                if(stk[top-1] != r) {
                    addedge(r, stk[top-1]);
                    stk[top-1] = r; V[tot++] = r;
                }
                stk[top++] = V[i];
            }
        }

        while(top > 2) 
            addedge(stk[top-2], stk[top-1]), --top;

        dfs(stk[1]);

        ecnt = 1;
        for(LL i = 0; i < tot; i++) dp[V[i]] = st[V[i]] = 0; 
        //cerr << rt << endl;
    }

    void solve(LL *V, LL k) {
        ans = 0;
        build(V, k);
        printf("%lld\n", ans);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt","r", stdin);
    freopen("ans.txt","w", stdout);
#endif


    n = read<int>(), m = read<int>();
    for(LL i = 0; i < m; i++) {
        static LL x, y, z;
        x = read<int>(), y = read<int>(), z = read<int>();
        cactus :: addedge(x, y, z);
    }

    tree :: init();
    cactus :: dfs(1);

    tree :: dep[1] = 1;
    tree :: dfs(1);

    q = read<int>();
    for(LL i = 0; i < q; i++) {
        static LL V[maxn], k;
        //cerr << "begin:" << endl;
        k = read<int>();
        for(LL j = 0; j < k; j++) V[j] = read<int>();
        Vtree :: solve(V, k);
        //cerr << "end." << endl;;
    }

    return 0;
}
