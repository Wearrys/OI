#include <bits/stdc++.h>

using std::pair;
using std::string;
using std::vector;

typedef long long ll;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back
#define mp std::make_pair
#define debug(...) fprintf(stderr, __VA_ARGS__)

template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;

template <typename T> T read(T& x) {
    T f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = 200000;
const int B = N;

int n, ty;
int o[B + 5];
pii id[N + 5];

namespace BL {

    int tot;
    int nxt[B + 5];
    vector<int> v[B + 5];

    void init() {
        tot = 1;
        nxt[0] = 1;
        id[0] = mp(1, 0), id[1] = mp(1, 1);
        v[1].push_back(0), v[1].push_back(1);
    }

    void insert(pii pos, int val) {
        int x = pos.fst, y = pos.snd;

        v[x].insert(v[x].begin() + y + 1, val); 

        if(v[x].size() >= B) {
            nxt[++ tot] = nxt[x];
            nxt[x] = tot;
            v[tot].push_back(v[x].back());
            v[x].pop_back();
            id[v[tot][0]] = mp(tot, 0);
        }
        for(int i = 0; i < (int) v[x].size(); ++i) id[v[x][i]] = mp(x, i);

        for(int i = 1, p = 1; i; ++p, i = nxt[i]) {
            o[i] = p;
        }
    }

    void output() {
        for (auto t : v[1]) {
            debug("%d(%d, %d) ", t, id[t].fst, id[t].snd);
        }
        debug("\n");
    }
}

inline bool cmp(pii x, pii y) { 
    if(o[x.fst] != o[y.fst]) 
        return o[x.fst] < o[y.fst];
    return x.snd <= y.snd;
}

inline int _min(int x, int y) { return (x == 0 || y == 0) ? x + y : (cmp(id[x], id[y]) ? x : y); }
inline int _max(int x, int y) { return (x == 0 || y == 0) ? x + y : (cmp(id[x], id[y]) ? y : x); }

namespace SEG_T {

#define lc (u << 1)
#define rc (u << 1 | 1)
#define mid ((l + r) >> 1)

    const int SZ = N << 2;

    int mn[SZ + 5], mx[SZ + 5];

    void modify(int u, int l, int r, int p) {
        if(l == r) { mn[u] = mx[u] = l; return; }
        (p <= mid) ? modify(lc, l, mid, p) : modify(rc, mid+1, r, p);
        mx[u] = _max(mx[lc], mx[rc]);
        mn[u] = _min(mn[lc], mn[rc]);
    }

    inline int query_min(int u, int l, int r, int x, int y) {
        if(x <= l && r <= y) return mn[u];
        if(y <= mid) return query_min(lc, l, mid, x, y);
        if(mid < x) return query_min(rc, mid+1, r, x, y);
        return _min(query_min(lc, l, mid, x, y), query_min(rc, mid+1, r, x, y));
    }

    inline int query_max(int u, int l, int r, int x, int y) {
        if(x <= l && r <= y) return mx[u];
        if(y <= mid) return query_max(lc, l, mid, x, y);
        if(mid < x) return query_max(rc, mid+1, r, x, y);
        return _max(query_max(lc, l, mid, x, y), query_max(rc, mid+1, r, x, y));
    }
}

int fa[N + 5];
int pre[N + 5], nxt[N + 5];
int findset(int x) { return (x == fa[x]) ? x : fa[x] = findset(fa[x]); }

void init() {
    int nul; 
    read(nul);
    BL::init();
    SEG_T::modify(1, 1, n, 1);
    nxt[0] = pre[n + 1] = 1;
    pre[1] = 0, nxt[1] = n + 1;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(ty);

    init();

    int lans;
    printf("%d ", lans = 1);

    auto merge = [&] (int x, int y) {
        x = findset(x);
        y = findset(y);
        if(x ^ y) -- lans, fa[x] = y;
    };

    for(int i = 1; i <= n; ++i) fa[i] = i;
    for(int i = 2; i <= n; ++i) {
        static int k, l, r;
        static pii q[N + 5];
        int mn = 0, mx = 0, lst = 0;

        ++ lans;
        read(k);

        for(int j = 0; j < k; ++j) {
            read(q[j].fst), read(q[j].snd);

            if(ty) {
                q[j].fst = (q[j].fst + lans - 1) % i;
                q[j].snd = (q[j].snd + lans - 1) % i;
            }
        }
        std::sort(q, q + k);

        for(int j = 0; j < k; ++j) {
            l = q[j].fst, r = q[j].snd;

            if(lst + 1 <= l - 1) 
                mn = _min(mn, SEG_T::query_min(1, 1, n, lst + 1, l - 1));
            mx = _max(mx, SEG_T::query_max(1, 1, n, l, r)); 

            lst = r;
        }

        if(lst + 1 <= i - 1) 
            mn = _min(mn, SEG_T::query_min(1, 1, n, lst + 1, i - 1));

        if(mx && mn && cmp(id[mn], id[mx])) {
            mx = findset(mx);
            mn = findset(mn);

            pre[i] = mx, nxt[i] = nxt[mx];
            pre[nxt[i]] = nxt[pre[i]] = i;
            for(int j = mn; j != i; j = nxt[j]) {
                merge(j, i);
                pre[nxt[j]] = pre[j];
                nxt[pre[j]] = nxt[j];
            }
        } else {
            mx = findset(mx);
            pre[i] = mx, nxt[i] = nxt[mx];
            pre[nxt[i]] = nxt[pre[i]] = i;
        }

        BL::insert(id[mx], i);
        SEG_T::modify(1, 1, n, i);

        printf("%d ", lans);
    }

    return 0;
}
