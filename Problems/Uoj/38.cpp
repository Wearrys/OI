#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb push_back
#define REP(i, a, b)  for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i=(a-1), i##end = (b); i >=i##end; --i)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const int mod = 19961993;
const int oo = 0x3f3f3f3f;
const int maxn = 100000 + 10;

const int Prime[] = { 
    2, 3, 5, 7, 11, 13, 17, 19, 23, 
    29, 31, 37, 41, 43, 47, 53, 59, 
    61, 67, 71, 73, 79, 83, 89, 97, 
    101, 103, 107, 109, 113, 127, 131, 
    137, 139, 149, 151, 157, 163, 167, 
    173, 179, 181, 191, 193, 197, 199, 
    211, 223, 227, 229, 233, 239, 241, 
    251, 257, 263, 269, 271, 277, 281
};

const int Inv[] = {
    9980997, 13307996, 7984798, 11406854, 
    14517814, 18426456, 9393880, 5253157,
    16490343, 8260136, 2575742, 18343454,
    3895024, 17640832, 1698894, 3013132,
    7443456, 4581442, 9236147, 18275065,
    6562848, 2779519, 7936697, 4037258,
    6379607, 19566707, 13566404, 4104336,
    3662752, 13602421, 16661192, 1219054,
    13259427, 9047523, 3751248, 8196316,
    14621843, 1714528, 12192356, 11884887,
    8029406, 13455046, 17976246, 13342473,
    14084859, 15548287, 10217514, 9846724,
    5364237, 3486812, 1627803, 14950615,
    1076789, 12406658, 19340609, 8652728,
    7791857, 7955334, 1657495, 8808852, 
};

template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

typedef bitset<60> type;

namespace Seg_T {

#define lc (u << 1)
#define rc (lc | 1)
#define mid ((l + r) >> 1)

    type t[maxn << 2];
    LL Mul[maxn << 2];

    pair<type, LL> merge(pair<type, LL> a, pair<type, LL> b) {
        return make_pair(a.fst | b.fst, a.snd * b.snd % mod); 
    }
    void push_up(int u) {
        t[u] = t[lc] | t[rc];
        Mul[u] = Mul[lc] * Mul[rc] % mod;
    }
    void build(int u, int l, int r) {
        if(l == r) {
            Mul[u] = 3;
            t[u][1] = 1;
            return;
        }

        build(lc, l, mid);
        build(rc, mid+1, r);
        
        push_up(u);
    }
    void modify(int u, int l, int r, int x, int v) {
        if(l == r) {
            for(int i = 0; i < 60; ++i) 
                t[u][i] = bool(v % Prime[i] == 0);
            Mul[u] = v;
            return;
        }

        if(x <= mid) modify(lc, l, mid, x, v);
        else modify(rc, mid+1, r, x, v);

        push_up(u);
    }
    pair<type, LL> query(int u, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            return make_pair(t[u], Mul[u]);
        }

        if(x > mid) return query(rc, mid+1, r, x, y);
        if(y <= mid) return query(lc, l, mid, x, y);

        return merge(query(lc, l, mid, x, y), query(rc, mid+1, r, x, y));
    }
}

int m;
int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif
    
    Seg_T::build(1, 1, 100000);
    scanf("%d", &m);

    while(m--) {
        int op, l, r;
        op = read<int>(), l = read<int>(), r = read<int>();

        if(op) Seg_T::modify(1, 1, 100000, l, r);
        else {
            pair<type, LL> Ans = Seg_T::query(1, 1, 100000, l, r);

            for(int i = 0; i < 60; ++i) if(Ans.fst[i]) {
                (Ans.snd *= Inv[i]) %= mod;
            }
            printf("%lld\n", Ans.snd);
        }
    }
    return 0;
}
