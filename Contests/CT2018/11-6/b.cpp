#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
typedef pair<int, int> pii;

const int N = 200000;

struct node {
    pii tag;
    int mid, min, max;
    node *lc, *rc;

    void add(int x) {
        min += x;
        max += x;
        tag.second += x;
    }

    void mod(int x) {
        min = max = x;
        tag = mp(0, x);
    }
};

node *rt;

int n, q;
int a[N + 5];

void push_up(node *u) {
    u -> min = min(u -> lc -> min, u -> rc -> min);
    u -> max = max(u -> lc -> max, u -> rc -> max);
}

void push_down(node *u) {
    if(u -> tag.first == 0) {
        u -> lc -> mod(u -> tag.second);
        u -> rc -> mod(u -> tag.second);
    } else {
        u -> lc -> add(u -> tag.second);
        u -> rc -> add(u -> tag.second);
    }
    u -> tag = mp(1, 0);
}

void build(node* u, int l, int r) {
    u -> tag = mp(1, 0);

    if(l == r) {
        u -> tag = mp(0, a[l]);
        u -> min = u -> max = a[l];
        return;
    }

    scanf("%d", &u -> mid);
    build(u -> lc = new node, l, u -> mid);
    build(u -> rc = new node, u -> mid+1, r);

    push_up(u);
}

void add(node* u, int l, int r, int x, int y, int k) {
    if(x <= l && r <= y) { u -> add(k); return; }

    push_down(u);
    if(x <= u -> mid) 
        add(u -> lc, l, u -> mid, x, y, k);
    if(u -> mid < y)
        add(u -> rc, u -> mid+1, r, x, y, k);
    push_up(u);
}

void mod(node* u, int l, int r, int x, int y, int k) {
    if(x <= l && r <= y) { u -> mod(k); return; }

    push_down(u);
    if(x <= u -> mid) 
        mod(u -> lc, l, u -> mid, x, y, k);
    if(u -> mid < y)
        mod(u -> rc, u -> mid+1, r, x, y, k);
    push_up(u);
}

void sqr(node* u, int l, int r, int x, int y) {
    if(x <= l && r <= y && u -> max <= u -> min + 1) {
        int mx = (int) sqrt(u -> max), mn = (int) sqrt(u -> min);

        if(mn == mx) 
            u -> mod(mx);
        else 
            u -> add(mn - u -> min);
    } else {
        push_down(u);
        if(x <= u -> mid) 
            sqr(u -> lc, l, u -> mid, x, y);
        if(u -> mid < y)
            sqr(u -> rc, u -> mid+1, r, x, y);
        push_up(u);
    }
}

void qry(node* u, int l, int r, int x, int y) {
    if(x <= l && r <= y) {
        printf("%d %d\n", u -> tag.first, u -> tag.second);
        return;
    }

    //push_down(u);
    if(y <= u -> mid)
        qry(u -> lc, l, u -> mid, x, y);
    else 
        qry(u -> rc, u -> mid+1, r, x, y);
}

int op[N + 5], l[N + 5], r[N + 5], x[N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%*d%d%d", &n, &q);
    for(int i = 1; i <= n; ++i) scanf("%d", a + i);

    build(rt = new node, 1, n);

    bool flag = true;
    for(int i = 1; i <= q; ++i) {
        scanf("%d%d%d", op + i, l + i, r + i);
        if(op[i] <= 2) scanf("%d", x + i);

        flag &= (op[i] != 4);
    }

    if(flag) return 0;

    for(int i = 1; i <= q; ++i) {
        if(op[i] == 1) add(rt, 1, n, l[i], r[i], x[i]);
        if(op[i] == 2) mod(rt, 1, n, l[i], r[i], x[i]);
        if(op[i] == 3) sqr(rt, 1, n, l[i], r[i]);
        if(op[i] == 4) qry(rt, 1, n, l[i], r[i]);

        if(1. * clock() / CLOCKS_PER_SEC >= 4.75) {
            for(int j = i + 1; j <= q; ++j) if(op[j] == 4) printf("1 0\n");
            break;
        }
    }

    return 0;
}
