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
 
const int N = 100000;
const int oo = 0x3f3f3f3f;
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

namespace Seg_T {
#define lc (u << 1)
#define rc (u << 1 | 1)
#define mid ((l + r) >> 1)

    const int SZ = N << 2;

    int sum1[SZ + 5], sum2[SZ + 5];

    void clear() {
        memset(sum1, 0, sizeof sum1);
        memset(sum2, 0, sizeof sum2);
    }
    void modify1(int u, int l, int r, int p, int v) {
        if(l == r) { sum1[u] += v; return; }

        if(p <= mid) 
            modify1(lc, l, mid, p, v);
        else 
            modify1(rc, mid+1, r, p, v);

        sum1[u] = sum1[lc] + sum1[rc];
    }

    void modify2(int u, int l, int r, int p, int v) {
        if(l == r) { sum2[u] += v; return; }

        if(p <= mid) 
            modify2(lc, l, mid, p, v);
        else 
            modify2(rc, mid+1, r, p, v);

        sum2[u] = sum2[lc] + sum2[rc];
    }

    int query1(int u, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            return sum1[u];
        }
        
        int ans = 0;
        if(x <= mid) ans += query1(lc, l, mid, x, y);
        if(mid < y) ans += query1(rc, mid+1, r, x, y);

        return ans;
    }
    int query2(int u, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            return sum2[u];
        }
        
        int ans = 0;
        if(x <= mid) ans += query2(lc, l, mid, x, y);
        if(mid < y) ans += query2(rc, mid+1, r, x, y);

        return ans;
    }
    int query_min(int u, int l, int r) {
        if(l == r) return l;
        if(sum2[lc]) 
            return query_min(lc, l, mid);
        return query_min(rc, mid+1, r);
    }
}

int n, q;
int s[N + 5];
int head[N + 5];
vector<int> G[N + 5];
std::priority_queue<pii, vector<pii>, std::greater<pii> > rm;

int main() {
#ifdef Wearry
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif 

    int T;
    read(T);
    while(T--) {

        read(n);
        for(int i = 1; i <= n; ++i) read(s[i]);

        Seg_T::clear();
        while(rm.size()) rm.pop();
        for(int i = 1; i <= n; ++i) G[i].clear(), head[i] = 0;

        read(q);
        for(int i = 1; i <= q; ++i) {
            static int t, op, id, l, r;

            read(t), read(op);
            while(!rm.empty() && rm.top().fst <= t) {
                head[id = rm.top().snd] ++;
                Seg_T::modify1(1, 1, n, id, -1);
                Seg_T::modify2(1, 1, n, id, +1); rm.pop();
            }

            if(op == 0) {
                read(id);
                G[id].pb(t);
                rm.push(mp(t + s[id], id));
                Seg_T::modify1(1, 1, n, id, 1);
            } 
            if(op == 1) {
                if(Seg_T::sum2[1]) {
                    printf("%d\n", id = Seg_T::query_min(1, 1, n));
                    Seg_T::modify2(1, 1, n, id, -1);
                } else puts("Yazid is angry.");
            }
            if(op == 2) {
                read(id);
                if(Seg_T::query2(1, 1, n, id, id)) {
                    puts("Succeeded!");
                    Seg_T::modify2(1, 1, n, id, -1);
                } else if(Seg_T::query1(1, 1, n, id, id)) {
                    printf("%d\n", s[id] - (t - G[id][head[id]])); 
                } else {
                    puts("YJQQQAQ is angry.");
                }
            }
            if(op == 3) {
                read(l), read(r);
                printf("%d\n", Seg_T::query2(1, 1, n, l, r));
            }
        }
    }

    return 0;
}
