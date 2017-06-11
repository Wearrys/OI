#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back
#define getchar getchar_unlocked

template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;
const int maxn = 1e5 + 5;
const int mod = 998244353;

int read() {
	int n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48;
	return n * f;
}

inline int merge(int a, int b) {
    return (a * (1LL - b + mod) % mod + b * (1LL - a + mod) % mod) % mod;
}

int N, M, prob;
namespace Seg_Tree {
    const int SZ_X = (maxn << 2) + 5;
    const int SZ_Y = (maxn * 400) + 5;

    int rt[SZ_X];
    int val[SZ_Y];
    int lc[SZ_Y], rc[SZ_Y], cnt;

#define LC (u << 1) 
#define RC (LC | 1)
#define mid ((l+r) >> 1)

    void Add_Y(int& u, int l, int r, int x, int y) {
        if(!u) u = ++cnt;
        if(x <= l && r <= y) {
            val[u] = merge(val[u], prob);
            return;
        }
        if(x <= mid) Add_Y(lc[u], l, mid, x, y);
        if(y > mid) Add_Y(rc[u], mid+1, r, x, y);
    }
    void Add_X(int u, int l, int r, int x, int y, int x0, int y0) {
        if(x <= l && r <= y) {
            Add_Y(rt[u], 0, N, x0, y0);
            return;
        }
        if(x <= mid) Add_X(LC, l, mid, x, y, x0, y0);
        if(y > mid) Add_X(RC, mid+1, r, x, y, x0, y0);
    }
    int query_Y(int u, int l, int r, int x) {
        if(l == r) return val[u];
        return merge(val[u], 
                x <= mid ? query_Y(lc[u], l, mid, x) : query_Y(rc[u], mid+1, r, x));
    }
    int query_X(int u, int l, int r, int x, int x0) {
        if(l == r) return query_Y(rt[u], 0, N, x0);

        return merge(query_Y(rt[u], 0, N, x0), 
                x <= mid ? query_X(LC, l, mid, x, x0) : query_X(RC, mid+1, r, x, x0));
    }
}

int fpm(int base, int exp) {
    int res = 1;
    for(; exp > 0; exp >>= 1) {
        if(exp & 1) 
            res = 1LL * res * base % mod;
        base = 1LL * base * base % mod;
    }
    return res;
}

int tot = 0;
void solve() {
    N = read(); M = read();
    while(M--) {
        static int ty, l, r;
        ty = read(); l = read(); r = read();
        if(ty == 1) {
            static LL tmp; 
            tmp = fpm(r-l+1, mod-2);
            prob = 2*tmp; Seg_Tree::Add_X(1, 0, N, l, r, l, r); 
            prob = tmp; Seg_Tree::Add_X(1, 0, N, l, r, r+1, N);
            prob = tmp; Seg_Tree::Add_X(1, 0, N, 0, l-1, l, r);

            ++ tot;
        }else {
            static int ans;
            ans = (1-Seg_Tree::query_X(1, 0, N, l-1, r)+mod) % mod;
            if(!(l-1) && (tot & 1))
                ans = (1-ans+mod) % mod;
            printf("%d\n", ans);
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    solve();
    return 0;
}
