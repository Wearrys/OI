#include <bits/stdc++.h>
using namespace std;

#define bitcnt __builtin_popcount

const int N = 1000000;

int n, q;
int a[N + 5];

map <pair<int, int>, int> mp;

struct node {
    int m;
    int v;
    long long res;
    int lc, rc;
};

int cnt;
node t[N + 5];

int build(int l, int r) {
    int u = ++ cnt;
    mp[make_pair(l, r)] = u;

    if(l == r) {
        t[u].v = t[u].res = a[l];
        return u;
    }

    scanf("%d", &t[u].m);

    t[u].lc = build(l, t[u].m);
    t[u].rc = build(t[u].m + 1, r);

    t[u].v = t[t[u].lc].v & t[t[u].rc].v;
    t[u].res = t[u].v + ((bitcnt(t[u].v) & 1) ? t[t[u].lc].res : t[t[u].rc].res);

    return u;
}

void modify(int u, int l, int r, int x, int y, int val, int op) {
    int mid = t[u].m;

    if(l == r) {
        if(op == 1) t[u].v &= val;
        if(op == 2) t[u].v |= val;
        if(op == 3) t[u].v ^= val;
        t[u].res = t[u].v;
        return;
    }

    if(x <= mid) 
        modify(t[u].lc, l, mid, x, y, val, op);
    if(mid < y)
        modify(t[u].rc, mid+1, r, x, y, val, op);

    t[u].v = t[t[u].lc].v & t[t[u].rc].v;
    t[u].res = t[u].v + ((bitcnt(t[u].v) & 1) ? t[t[u].lc].res : t[t[u].rc].res);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; ++i) scanf("%d", a + i);

    build(1, n);
    for(int i = 1; i <= q; ++i) {
        static int op, l, r, x;
        scanf("%d%d%d", &op, &l, &r);
        if(op != 4) scanf("%d", &x);

        if(op <= 3) 
            modify(1, 1, n, l, r, x, op);
        else 
            printf("%lld\n", t[mp[make_pair(l, r)]].res);
    }

    return 0;
}
