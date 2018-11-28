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

string procStatus() {
    std::ifstream t("/proc/self/status");
    return string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}

template <typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = 2000000;

struct tag {
    int a, x;
    tag(int _a = ~0, int _x = 0): a(_a), x(_x) { }

    void clear() { a = ~0, x = 0; }
    bool empty() { return (!(~a)) && !x; }
    void moda(int v) { a &= v, x &= v; }
    void modo(int v) { a &= ~v, x |= v; }
    void modx(int v) { x ^= v; }

    tag operator + (const tag& rhs) const {
        return tag(a & rhs.a, (x & rhs.a) ^ rhs.x);
    }
};

struct atom {
    int a, o;
    atom(int _a = ~0, int _o = 0): a(_a), o(_o) { }

    void mod(const tag& t) {
        a &= t.a, o &= t.a;
        int s = ~(a^o) & t.x;
        a ^= s, o ^= s;
    }

    atom operator + (const atom& rhs) const {
        return atom(a & rhs.a, o | rhs.o);
    }
};

atom sub_tree[N + 5], lson[N + 5];

namespace seg_t {

    const int SZ = N << 2;

#define lc (u << 1)
#define rc (u << 1 | 1)
#define mid ((l + r) >> 1)

    struct node {
        atom s;
        tag t;

        void mod(const tag& _t) {
            s.mod(_t);
            t = t + _t;
        }
    };

    node t[SZ + 5];

    void push_up(int u) { t[u].s = t[lc].s + t[rc].s; }

    void push_down(int u) {
        if(!t[u].t.empty()) {
            t[lc].mod(t[u].t);
            t[rc].mod(t[u].t);
            t[u].t.clear();
        }
    }

    void build(int u, int l, int r) {
        if(l == r) { t[u].s = lson[l]; return; }
        build(lc, l, mid);
        build(rc, mid+1, r);
        push_up(u);
    }

    void modify(int u, int l, int r, int x, int y, tag v) {
        if(x <= l && r <= y) { t[u].mod(v); return; }
        push_down(u);
        if(x <= mid) modify(lc, l, mid, x, y, v);
        if(mid < y) modify(rc, mid+1, r, x, y, v);
        push_up(u);
    }

    void modify(int u, int l, int r, int p, atom v) {
        if(l == r) { t[u].s = v; t[u].t.clear(); return; }
        push_down(u);
        (p <= mid) ? modify(lc, l, mid, p, v) : modify(rc, mid+1, r, p, v);
        push_up(u);
    }

    atom query(int u, int l, int r, int x, int y) {
        if(x <= l && r <= y) return t[u].s;
        push_down(u);
        if(y <= mid) return query(lc, l, mid, x, y);
        if(mid < x) return query(rc, mid+1, r, x, y);
        return query(lc, l, mid, x, y) + query(rc, mid+1, r, x, y);
    }

    int as, pos;
    void find(int u, int l, int r, int y, int v) {
        if(r <= y && (as & t[u].s.a) > v) { as &= t[u].s.a; pos = l; return; }
        if(l == r) return;

        push_down(u);

        if(y <= mid) {
            find(lc, l, mid, y, v);
        } else {
            find(rc, mid+1, r, y, v);

            if(pos == mid + 1) {
                find(lc, l, mid, y, v);
            }
        }
    }

    int find_pos(int m, int y, int v) {
        as = ~0;
        pos = y + 1;
        find(1, 1, m, y, v);
        if(pos == y+1) pos = y;
        return pos;
    }

#undef lc
#undef rc
#undef mid
}

int n, m, q;
int a[N + 5];
std::map <pii, int> idx;

int val[N + 5], sz[N + 5], c[N + 5][2];
int len[N + 5], dir[N + 5], son[N + 5];

int input(int l, int r) {
    int u = ++ m, mid;
    idx[mp(l, r)] = u;
    if(l == r) { val[u] = a[l]; sz[u] = 1; return u; }

    read(mid);
    c[u][0] = input(l, mid);
    c[u][1] = input(mid+1, r);

    sz[u] = sz[c[u][0]] + sz[c[u][1]];
    dir[u] = sz[c[u][0]] > sz[c[u][1]] ? 0 : 1;
    son[u] = sz[c[u][0]] > sz[c[u][1]] ? c[u][0] : c[u][1];
    len[u] = (dir[son[u]] == dir[u] && son[son[u]]) ? len[son[u]] + 1 : 1;

    return u;
}

int dfn[N + 5], efn[N + 5], dfc;
int fa[N + 5], top[N + 5], bot[N + 5], seq[N + 5];

void dfs(int u, int t, int f) {
    fa[u] = f;
    top[u] = t;
    dfn[u] = ++ dfc;
    seq[dfc] = u;

    if(!son[u]) {
        bot[u] = u;
        sub_tree[u] = lson[dfn[u]] = atom(val[u], val[u]);
    } else {
        dfs(son[u], t, u);
        int l_son = c[u][dir[u] ^ 1];
        dfs(l_son, l_son, u);

        bot[u] = bot[son[u]];
        lson[dfn[u]] = sub_tree[l_son];
        sub_tree[u] = sub_tree[l_son] + sub_tree[son[u]];
    }

    efn[u] = dfc;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n); read(q);
    for(int i = 1; i <= n; ++i) read(a[i]);

    input(1, n);
    dfs(1, 1, 0);
    seg_t::build(1, 1, m);

    for(int i = 1; i <= q; ++i) {
        static int op, l, r, x;

        read(op), read(l), read(r);

        if(op < 4) {
            read(x);
            tag tmp;
            if(op == 1) tmp.moda(x);
            if(op == 2) tmp.modo(x);
            if(op == 3) tmp.modx(x);

            int u = idx[mp(l, r)];
            seg_t::modify(1, 1, m, dfn[u], efn[u], tmp);

            u = top[u];
            while(fa[u]) {
                atom subt = seg_t::query(1, 1, m, dfn[u], dfn[bot[u]]);
                seg_t::modify(1, 1, m, dfn[fa[u]], subt);
                u = top[fa[u]];
            }
        } else {
            ll ans = 0;
            int u = idx[mp(l, r)];

            while(true) {
                atom cur = seg_t::query(1, 1, m, dfn[u], dfn[bot[u]]);
                bool d = (__builtin_popcount(cur.a) & 1) ^ 1;

                if(!son[u]) { ans += cur.a; break; }
                if(d ^ dir[u]) {
                    ans += cur.a;
                    u = c[u][d];
                    continue;
                }

                int p = seg_t::find_pos(m, dfn[bot[u]], cur.a);

                if(p > dfn[u] + len[u]) {
                    ans += 1ll * cur.a * (len[u] + 1);
                    u = seq[dfn[u] + len[u]];
                    if(!son[u]) break;
                    u = c[u][d];
                    continue;
                }

                ans += 1ll * cur.a * (p - dfn[u]); 
                u = seq[p];
            }
            printf("%lld\n", ans);
        }
    }

    return 0;
}
