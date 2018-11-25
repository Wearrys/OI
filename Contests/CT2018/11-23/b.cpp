#include <bits/stdc++.h>
using namespace std;

const int N = 400000;
const int oo = 0x3f3f3f3f;

typedef long long ll;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back
#define mp make_pair

template <typename T> inline bool chkmin(T& a, T b) {
    return a > b ? a = b, 1 : 0;
}

template <typename T> T read(T& x) {
    T f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

namespace G {
    const int SZ = N << 7;

    int st[SZ + 5], to[SZ + 5], nxt[SZ + 5], w[SZ + 5], e = 1;

    inline void addedge(int x, int y, int z) {
        to[++ e] = y; nxt[e] = st[x]; st[x] = e; w[e] = z;
    }

    int bfs(vector<int> a, vector<int> b) {
        static int dis[SZ + 5];
        memset(dis, oo, sizeof dis);

        deque<int> que;
        for(auto v : a) dis[v] = 1, que.push_back(v);

        while(!que.empty()) {
            int x = que.front(); que.pop_front();

            for(int i = st[x]; i; i = nxt[i]) {
                int y = to[i];
                if(chkmin(dis[y], dis[x] + w[i])) {
                    if(w[i]) {
                        que.push_back(y);
                    } else {
                        que.push_front(y);
                    }
                }
            }
        }

        int res = oo;
        for(auto v : b) chkmin(res, dis[v]);
        return res;
    }
}

int idx;
namespace SEG {
    const int SZ = N << 2;

#define lc (u << 1)
#define rc (u << 1 | 1)
#define mid ((l + r) >> 1)

    int id[SZ + 5];
    void clear() { memset(id, 0, sizeof id); }

    void add(int u, int l, int r, int p, int x) {
        id[u] = ++ idx;
        if(l == r) { if(x > 0) G::addedge(id[u], x, 1); return; }
        (p <= mid) ? add(lc, l, mid, p, x) : add(rc, mid+1, r, p, x);
        
        if(id[lc]) G::addedge(id[u], id[lc], 0);
        if(id[rc]) G::addedge(id[u], id[rc], 0);
    }

    void query(int u, int l, int r, int x, int y, int v) {
        if(!id[u]) return;
        if(x <= l && r <= y) { G::addedge(v, id[u], 0); return; }
        if(x <= mid) query(lc, l, mid, x, y, v);
        if(mid < y) query(rc, mid+1, r, x, y, v);
    }
}

int n, nx, ny;
vector<int> x, y;
int sx, sy, tx, ty;

struct node { int x, l, r; };
struct block { int l, r, d, u; };

bool operator < (const node& a, const node& b) {
    if(a.x != b.x) return a.x < b.x;
    if(a.l != b.l) return a.l < b.l;
    if(a.r != b.r) return a.r < b.r;
    return false;
}

bool operator == (const node& a, const node& b) {
    return (a.x == b.x) && (a.l == b.l) && (a.r == b.r);
}

block b[N + 5];
node hs, vs, ht, vt;
vector<node> ver, hor;
vector<pii> mod[3][N + 5];

set<pii> s;
set<pii>::iterator it;

node get_node(int p, pii t) {
    it = s.upper_bound(t);
    int r = it -> first; -- it;
    int l = it -> second;
    return (node) { p, l, r };
}

void scan() {
    s.clear();
    for(int i = 1; i <= nx; ++i) for(int d = 0; d < 3; ++d) mod[d][i].clear();
    for(int i = 1; i <= n; ++i) {
        mod[2][b[i].l].pb(mp(b[i].d, b[i].u));
        mod[1][b[i].l].pb(mp(b[i].d, b[i].u));
        mod[1][b[i].r].pb(mp(b[i].d, b[i].u));
        mod[0][b[i].r].pb(mp(b[i].d, b[i].u));
    }

    s.insert(mp(-oo, 1));
    s.insert(mp(ny, oo));

    for(int i = 1; i <= nx; ++i) {
        for(auto p : mod[0][i]) s.erase(p);
        for(auto p : mod[1][i]) ver.pb(get_node(i, p));
        if(i == sx) ver.pb(vs = get_node(i, mp(sy, sy)));
        if(i == tx) ver.pb(vt = get_node(i, mp(ty, ty)));
        for(auto p : mod[2][i]) s.insert(p);
    }

    s.clear();
    for(int i = 1; i <= nx; ++i) for(int d = 0; d < 3; ++d) mod[d][i].clear();
    for(int i = 1; i <= n; ++i) {
        mod[2][b[i].d].pb(mp(b[i].l, b[i].r));
        mod[1][b[i].d].pb(mp(b[i].l, b[i].r));
        mod[1][b[i].u].pb(mp(b[i].l, b[i].r));
        mod[0][b[i].u].pb(mp(b[i].l, b[i].r));
    }

    s.insert(mp(-oo, 1));
    s.insert(mp(nx, oo));

    for(int i = 1; i <= ny; ++i) {
        for(auto p : mod[0][i]) s.erase(p);
        for(auto p : mod[1][i]) hor.pb(get_node(i, p));
        if(i == sy) hor.pb(hs = get_node(i, mp(sx, sx)));
        if(i == ty) hor.pb(ht = get_node(i, mp(tx, tx)));
        for(auto p : mod[2][i]) s.insert(p);
    }

    sort(ver.begin(), ver.end()); ver.erase(unique(ver.begin(), ver.end()), ver.end());
    sort(hor.begin(), hor.end()); hor.erase(unique(hor.begin(), hor.end()), hor.end());
}

void build() {
    int vrs = ver.size();
    idx = ver.size() + hor.size();

    for(int i = 1; i <= nx; ++i) for(int d = 0; d < 2; ++d) mod[d][i].clear();
    for(int i = 0; i < (int) ver.size(); ++i) {
        auto p = ver[i];
        mod[1][p.x].pb(mp(i, 0));
    }
    for(int i = 0; i < (int) hor.size(); ++i) {
        auto p = hor[i];
        mod[0][p.l].pb(mp(i, +1));
        mod[0][p.r + 1].pb(mp(i, -1));
    }

    SEG::clear();
    for(int i = 1; i <= nx; ++i) {
        for(auto p : mod[0][i]) SEG::add(1, 1, ny, hor[p.fst].x, (p.fst + vrs + 1) * p.snd);
        for(auto p : mod[1][i]) SEG::query(1, 1, ny, ver[p.fst].l, ver[p.fst].r, p.fst + 1);
    }

    for(int i = 1; i <= ny; ++i) for(int d = 0; d < 2; ++d) mod[d][i].clear();
    for(int i = 0; i < (int) hor.size(); ++i) {
        auto p = hor[i];
        mod[1][p.x].pb(mp(i, 0));
    }
    for(int i = 0; i < (int) ver.size(); ++i) {
        auto p = ver[i];
        mod[0][p.l].pb(mp(i, +1));
        mod[0][p.r + 1].pb(mp(i, -1));
    }

    SEG::clear();
    for(int i = 1; i <= ny; ++i) {
        for(auto p : mod[0][i]) SEG::add(1, 1, nx, ver[p.fst].x, (p.fst + 1) * p.snd);
        for(auto p : mod[1][i]) SEG::query(1, 1, nx, hor[p.fst].l, hor[p.fst].r, p.fst + vrs + 1);
    }

    vector<int> S, T;
    for(int i = 0; i < (int) ver.size(); ++i) {
        if(ver[i] == vs) S.pb(i + 1);
        if(ver[i] == vt) T.pb(i + 1);
    }

    for(int i = 0; i < (int) hor.size(); ++i) {
        if(hor[i] == hs) S.pb(i + vrs + 1);
        if(hor[i] == ht) T.pb(i + vrs + 1);
    }

    printf("%d\n", G::bfs(S, T));
}

void input() {
    read(sx), read(sy), read(tx), read(ty), read(n);
    x.pb(sx), x.pb(tx), y.pb(sy), y.pb(ty);

    for(int i = 1; i <= n; ++i) {
        static int l, r, d, u;
        read(l), read(r), read(d), read(u);
        b[i] = (block) { l, r, d, u };
        x.pb(l), x.pb(r), y.pb(d), y.pb(u);
    }

    sort(x.begin(), x.end()), x.erase(unique(x.begin(), x.end()), x.end());
    sort(y.begin(), y.end()), y.erase(unique(y.begin(), y.end()), y.end());

    nx = (int) x.size();
    ny = (int) y.size();

    sx = lower_bound(x.begin(), x.end(), sx) - x.begin() + 1;
    sy = lower_bound(y.begin(), y.end(), sy) - y.begin() + 1;
    tx = lower_bound(x.begin(), x.end(), tx) - x.begin() + 1;
    ty = lower_bound(y.begin(), y.end(), ty) - y.begin() + 1;

    for(int i = 1; i <= n; ++i) {
        b[i].l = lower_bound(x.begin(), x.end(), b[i].l) - x.begin() + 1;
        b[i].r = lower_bound(x.begin(), x.end(), b[i].r) - x.begin() + 1;
        b[i].d = lower_bound(y.begin(), y.end(), b[i].d) - y.begin() + 1;
        b[i].u = lower_bound(y.begin(), y.end(), b[i].u) - y.begin() + 1;
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    input();
    scan();
    build();

    return 0;
}
