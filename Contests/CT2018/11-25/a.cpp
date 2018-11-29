#include <bits/stdc++.h>
using namespace std;

const int D = 20;
const int N = 100000;

#define fst first 
#define snd second
#define mp make_pair

typedef long long ll;

template <typename T> inline bool chkmin(T& a, T b) {
    return a > b ? a = b, 1 : 0;
}

struct point {
    ll x, y;
    point(ll _x = 0, ll _y = 0): x(_x), y(_y) { }

    point operator - (const point& rhs) const {
        return point(x - rhs.x, y - rhs.y);
    }

    bool operator < (const point& rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

inline ll cross(const point& a, const point& b) {
    return a.x * b.y - a.y * b.x;
}

int m;
namespace seg_t {
    const int SZ = N << 2;

#define lc (u << 1)
#define rc (u << 1 | 1)
#define mid ((l + r) >> 1)

    vector <point> H[SZ + 5];
    int lst[D + 5], cur[SZ + 5];

    void push_up(int u) {
        vector <point> temp;
        temp.resize(H[lc].size() + H[rc].size());
        merge(H[lc].begin(), H[lc].end(), H[rc].begin(), H[rc].end(), temp.begin());

        cur[u] = 0;
        H[u].clear();
        for(auto p : temp) {
            while(H[u].size() > 1 && cross(p - H[u][H[u].size() - 2], H[u].back() - H[u][H[u].size() - 2]) >= 0)
                H[u].pop_back();
            H[u].push_back(p);
        }
    }

    void modify(int p, point v, int u = 1, int l = 1, int r = m, int d = 0) {
        if(l == r) { H[u].push_back(v); return; }

        (p <= mid) ? modify(p, v, lc, l, mid, d + 1) : modify(p, v, rc, mid+1, r, d + 1);

        if(p == r) {
            if(lst[d])
                push_up(lst[d]);
            lst[d] = u;
        }
    }

    void remove(int p, int u = 1, int l = 1, int r = m, int d = 0) {
        H[u].clear();
        if(l == r) return;
        if(lst[d] == u) lst[d] = 0;

        (p <= mid) ? remove(p, lc, l, mid, d + 1) : remove(p, rc, mid+1, r, d + 1);
    }

    ll query(int x, int y, ll w, int u = 1, int l = 1, int r = m) {
        if(H[u].size() && x <= l && r <= y) {
            int &c = cur[u];
            while(c < (int) H[u].size() - 1 && w * H[u][c + 1].x + H[u][c + 1].y <= w * H[u][c].x + H[u][c].y)
                ++ c;
            return H[u][c].x * w + H[u][c].y;
        }

        ll ans = LLONG_MAX;
        if(x <= mid) chkmin(ans, query(x, y, w, lc, l, mid));
        if(mid < y) chkmin(ans, query(x, y, w, rc, mid+1, r));
        return ans;
    }
}

int lg[N + 5];
ll mn[N + 5][20];
ll f[N + 5], w[N + 5];

ll qmin(int l, int r) {
    int k = lg[r - l + 1];
    return min(mn[r][k], mn[l + (1 << k) - 1][k]);
}

int n;
int l[N + 5], t[N + 5];

void input() {
    scanf("%d", &n);
    for(m = 1; m < n; m <<= 1);
    for(int i = 1; i <= n; ++i) scanf("%d%d%lld", l + i, t + i, w + i);
    for(int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
    for(int i = n-1; i >= 1; --i) w[i] += w[i + 1];
}

void solve() {
    static int stk[N + 5], top = 0;

    f[stk[top ++] = 0] = 0;
    for(int i = 1; i <= n; ++i) {
        while(top > 1 && t[stk[top-1]] <= t[i]) seg_t::remove(-- top);
        stk[top ++] = i;
        seg_t::modify(top-1, point(t[stk[top-1]], qmin(stk[top-2], stk[top-1]-1)));

        int p = upper_bound(stk, stk + top, l[i]) - stk;
        f[i] = min(qmin(l[i], stk[p] - 1) + t[stk[p]] * w[i+1], seg_t::query(p+1, top-1, w[i+1]));

        mn[i][0] = f[i];
        for(int j = 1; j < 20 && (1 << j) - 1 <= i; ++j) 
            mn[i][j] = min(mn[i][j-1], mn[i - (1 << (j - 1))][j-1]);
    }
    printf("%lld\n", f[n]);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    input();
    solve();

    return 0;
}
