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
const int M = 400000;
const int mo = 1e9 + 7;

int st[N + 5], to[M + 5], nxt[M + 5], w[M + 5], e = 1;

inline void addedge(int x, int y, int z) {
    to[++ e] = y;
    nxt[e] = st[x];
    st[x] = e; w[e] = z;
}

ll diss[N + 5], dist[N + 5];
bool vis[N + 5];

int n, m, S, T;
int cnts[N + 5], cntt[N + 5];
vector<int> pres[N + 5], pret[N + 5];

typedef pair<ll, int> pli;

void spfa(ll *dis, int *cnt, vector<int>* pre, int s) {
    std::priority_queue<pli, vector<pli>, std::greater<pli> > que;

    memset(vis, 0, sizeof vis);

    cnt[s] = 1;
    dis[s] = 0;
    que.push(mp(0, s));

    while(!que.empty()) {
        int x = que.top().snd; que.pop();
        if(vis[x]) continue;

        vis[x] = true;
        for(int i = st[x]; i; i = nxt[i]) {
            int y = to[i];
            if(vis[y]) continue;

            if(chkmin(dis[y], dis[x] + w[i])) {

                pre[y].clear();

                cnt[y] = cnt[x];
                pre[y].pb(x);
                que.push(mp(dis[y], y));

            } else if(dis[y] == dis[x] + w[i]) {

                cnt[y] = (cnt[x] + cnt[y]) % mo;
                pre[y].pb(x);
            }
        }
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif 

    read(n), read(m);
    read(S), read(T);

    for(int i = 1; i <= m; ++i) {
        static int x, y, z;
        read(x), read(y), read(z);
        addedge(x, y, z), addedge(y, x, z);
    }

    memset(diss, oo, sizeof diss);
    memset(dist, oo, sizeof dist);

    spfa(diss, cnts, pres, S);
    spfa(dist, cntt, pret, T);

    ll DIS = dist[S];
    ll ans = 1ll * cnts[T] * cntt[S] % mo;

    for(int i = 1; i <= n; ++i) {
        if(DIS % 2 == 0 && dist[i] == DIS / 2) {
            ans -= 1ll * cnts[i] * cnts[i] % mo * cntt[i] % mo * cntt[i] % mo;
            ans %= mo;
        } 
        if(diss[i] + dist[i] != DIS) continue;
        for(int j = 0; j < int(pret[i].size()); ++j) {
            int pre = pret[i][j];
            if(dist[pre] < DIS / 2 && dist[i] > (DIS+1) / 2) {
                ans -= 1ll * cntt[pre] * cntt[pre] % mo * cnts[i] % mo * cnts[i] % mo; 
                ans %= mo;
            }
        }
    }
    printf("%lld\n", (ans + mo) % mo);

    return 0;
}
