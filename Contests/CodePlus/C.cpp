#include <bits/stdc++.h>
#include <tr1/unordered_map>
#include <ext/pb_ds/priority_queue.hpp> //__gnu_pbds::priority_queue
 
using std::pair;
using std::vector;
using std::string;

typedef long long ll;
typedef unsigned long long ull;

typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb(a) push_back(a)
#define mp(a, b) std::make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const int N = 50000;
const int M = 100000;
const int oo = 0x3f3f3f3f;
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

typedef std::bitset<N + 5> Set;

struct Graph {
    int s, t, n;
    int st[N + 5], nxt[M + 5], to[M + 5], w[M + 5], e = 1;

    void init(int n_, int s_, int t_) {
        n = n_, s = s_, t = t_;
        memset(st, 0, sizeof st);
    }

    void addedge(int x, int y, int z) {
        to[++e] = y; nxt[e] = st[x]; st[x] = e; w[e] = z;
        to[++e] = x; nxt[e] = st[y]; st[y] = e; w[e] = z;
    }

    int cnt;
    ll dis[N + 5];
    pair<ll, int> q[2*M + 5];

    Set anc[N + 5];
    ull ways[N + 5];
    bool done[N + 5];

    int ind[N + 5];
    vector<int> G[N + 5];

    void dijkstra() {
        memset(dis, oo, sizeof dis);
        memset(done, 0, sizeof done);

        dis[s] = 0;
        q[cnt++] = mp(0, s);

        while(cnt) {
            int x = q[0].snd; 
            pop_heap(q, q + (cnt--), std::greater< pair<ll, int> >() );
            
            if(done[x]) continue; 
            done[x] = true;

            for(int i = st[x]; i; i = nxt[i]) {
                int y = to[i];
                if(!done[y] && chkmin(dis[y], dis[x] + w[i])) {
                    q[cnt++] = mp(dis[y], y);
                    push_heap(q, q + cnt, std::greater< pair<ll, int> >());
                }
            }
        }
    }

    void build(ll *dist) {
        for(int i = 1; i <= n; ++i) {
            for(int j = st[i]; j; j = nxt[j]) {
                if(dis[to[j]] == dis[i] + w[j] && 
                    dist[i] == dist[to[j]] + w[j]) G[i].pb(to[j]), ++ ind[to[j]];
            }
        }
    }
        
    void calc() {
        static int que[N + 5];
        static int head = 0, tail = 0;

        ways[s] = 1;
        anc[s].set(s);
        que[tail++] = s;
        
        while(head < tail) {
            int x = que[head++];

            for(int i = 0; i < int(G[x].size()); ++i) {
                int y = G[x][i];

                anc[y] |= anc[x];
                ways[y] += ways[x];
                if(!(--ind[y])) anc[y].set(y), que[tail++] = y;
            }
        }
    }
};

Graph g0, g1;

std::tr1::unordered_map<ull, Set> mp;

int n, m, S, T;
void solve() {
    read(n), read(m), read(S), read(T);

    g0.init(n, S, T);
    g1.init(n, T, S);

    for(int i = 1; i <= m; ++i) {
        static int x, y, z;
        read(x), read(y), read(z);
        g0.addedge(x, y, z);
        g1.addedge(x, y, z);
    }

    g0.dijkstra(); 
    g1.dijkstra();

    g0.build(g1.dis); g0.calc();
    g1.build(g0.dis); g1.calc();

    if(!g0.ways[T]) {
        printf("%lld\n", 1ll * n * (n - 1) / 2);
        return; 
    }

    ll ans = 0;
    ull all = g0.ways[T] * g1.ways[T];

    for(int i = 1; i <= n; ++i) {
        ull tmp = g0.ways[i] * g1.ways[i];
        ans = (ans + (mp[all - tmp] & (~g0.anc[i])).count());
        mp[tmp].set(i);
    }
    printf("%lld\n", ans);
}


int main() {
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);

    solve();

    return 0;
}
