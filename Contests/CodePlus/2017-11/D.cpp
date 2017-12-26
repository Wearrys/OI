#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp> //__gnu_pbds::priority_queue
 
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
 
const int N = 500000;
const int oo = 0x3f3f3f3f;
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

int n;
int a[N + 5];
vector<int> pos[N + 5];

namespace Seg_T {
#define lc (u << 1)
#define rc (u << 1 | 1)
#define mid ((l + r) >> 1)

    const int SIZE = N << 3;

    ll add[SIZE + 5];
    bool clr[SIZE + 5];
    ll s1[SIZE + 5], s2[SIZE + 5];

    inline ll calc(ll l, ll r) {
        return (l + r) * (r - l + 1) / 2;
    }

    void push_up(int u) {
        s1[u] = s1[lc] + s1[rc];
        s2[u] = s2[lc] + s2[rc];
    }

    void push_down(int u, int l, int r) {
        if(clr[u]) {
            clr[u] = 0;
            clr[lc] = clr[rc] = 1;
            add[lc] = s1[lc] = s2[lc] = 0;
            add[rc] = s1[rc] = s2[rc] = 0;
        }

        if(add[u]) {
            add[lc] += add[u];
            add[rc] += add[u];
            s1[lc] += add[u] * (mid - l + 1); s2[lc] += add[u] * calc(l, mid);
            s1[rc] += add[u] * (r - mid);     s2[rc] += add[u] * calc(mid+1, r);
        } add[u] = 0;
    }

    void modify(int u, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            add[u] ++;
            s1[u] += (r - l + 1);
            s2[u] += calc(l, r);
            return;
        }
        push_down(u, l, r);

        if(x <= mid) modify(lc, l, mid, x, y);
        if(mid < y) modify(rc, mid+1, r, x, y);

        push_up(u);
    }

    ll query(int u, int l, int r, int x, int y) {
        if(x > r || y < l) return 0;
        if(x <= l && r <= y) {
            return 1ll * (y + 1) * s1[u] - s2[u];
        }
        push_down(u, l, r);
        return query(lc, l, mid, x, y) + query(rc, mid+1, r, x, y);
    }
    ll query2(int u, int l, int r, int x, int y) {
        if(x > r || y < l) return 0;
        if(x <= l && r <= y) return s1[u];
        push_down(u, l, r);
        return query2(lc, l, mid, x, y) + query2(rc, mid+1, r, x, y);
    }
}

int tp;
int main() {
#ifdef Wearry
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif 

    read(n); read(tp);
    for(int i = 1; i <= n; ++i) {
        pos[read(a[i])].pb(i);
    }

    ll ans = 0;
    for(int i = 0; i < n; ++i) if(pos[i].size()) {

        pos[i].pb(n+1);
        Seg_T::modify(1, -n, n, 0, 0);

        int cur = 0, lst = 0;
        for(int j = 0; j < int(pos[i].size()); ++j) {
            int tmp = cur;
            cur -= (pos[i][j] - lst - 1);

            ans += Seg_T::query2(1, -n, n, -n, tmp-(pos[i][j]-lst-1)-2) * (pos[i][j] - lst - 1);
            ans += Seg_T::query(1, -n, n, tmp - (pos[i][j] - lst - 1) - 1, tmp - 2);
            Seg_T::modify(1, -n, n, cur, tmp - 1);

            lst = pos[i][j];

            if(lst != n+1) {
                ++ cur;
                ans += Seg_T::query2(1, -n, n, -n, cur - 1);
                Seg_T::modify(1, -n, n, cur, cur);
            }
        }

        Seg_T::clr[1] = 1;
        Seg_T::s1[1] = Seg_T::s2[1] = Seg_T::add[1] = 0;
    }
    printf("%lld\n", ans);

    return 0;
}
