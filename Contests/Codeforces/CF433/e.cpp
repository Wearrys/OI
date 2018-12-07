#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb push_back
#define eb emplace_back
#define REP(i, a, b)  for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i=(a-1), i##end = (b); i >=i##end; --i)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const int maxn = 200000 + 10;

template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

namespace bit {
#define lowbit(x) ((x) & -(x))
    int c[maxn];

    void init() {
        memset(c, 0, sizeof c);
    }
    void add(int x) {
        for(int i = x; i < maxn; i += lowbit(i)) {
            c[i] ++;
        }
    }
    int query(int x) {
        int ans = 0;
        for(int i = x; i > 0; i -= lowbit(i)) {
            ans += c[i];
        }
        return ans;
    }
}

int n, q;
int p[maxn];

struct Query {
    int l, d, r, u;
}Q[maxn];

struct nod {
    int u, d, id;
    nod(int u = 0, int d = 0, int id = 0): u(u), d(d), id(id) {}
};

LL ans[maxn];
vector<nod> que[2][maxn];

LL calc(LL a) {
    return 1LL * a * (a-1) / 2;
}

int main() {
#ifdef Wearry
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    cin >> n >> q;
    for(int i = 1; i <= n; ++i) p[i] = read<int>();

    for(int i = 1; i <= q; ++i) {
        Q[i].l = read<int>();
        Q[i].d = read<int>();
        Q[i].r = read<int>();
        Q[i].u = read<int>();

        que[0][Q[i].l].pb(nod(Q[i].u, Q[i].d, i));
        que[1][Q[i].r].pb(nod(Q[i].u, Q[i].d, i));
    }

    bit::init(); 
    for(int i = 1; i <= n; ++i) {
        if(que[0][i].size()) {
            for(int j = 0; j < int(que[0][i].size()); ++j) {
                ans[que[0][i][j].id] += calc(bit::query(que[0][i][j].d-1));
                ans[que[0][i][j].id] += calc(i-1-bit::query(que[0][i][j].u));
            }
        }
        bit::add(p[i]);
    }
    bit::init();
    for(int i = n; i >= 1; --i) {
        if(que[1][i].size()) {
            for(int j = 0; j < int(que[1][i].size()); ++j) {
                ans[que[1][i][j].id] += calc(bit::query(que[1][i][j].d-1));
                ans[que[1][i][j].id] += calc(n-i-bit::query(que[1][i][j].u));
            }
        }
        bit::add(p[i]);
    }

    for(int i = 1; i <= q; ++i) {
        LL res = calc(n);    
        res -= calc(Q[i].l-1);
        res -= calc(n-Q[i].r);
        res -= calc(Q[i].d-1);
        res -= calc(n-Q[i].u);
        res += ans[i];
        printf("%I64d\n", res);
    }

    return 0;
}
