#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;

long long a[N << 2];

template <typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

inline long long gcd(long long x, long long y) {
    if (x > 0) x >>= __builtin_ctz(x);
    if (y > 0) y >>= __builtin_ctz(y);

    if (x == 0) return y;
    if (y == 0) return x;

    if (x < y) swap(x, y);

    return gcd(x ^ y, y);
}

void modify(int u, int l, int r, int x, long long v) {
    if (l == r) {
        a[u] = v;
        while (a[u] > 0 && a[u] % 2 == 0) a[u] >>= 1;
        return;
    }

    int mid = (l + r) >> 1;
    if (x <= mid) {
        modify(u << 1, l, mid, x, v);
    } else {
        modify(u << 1 | 1, mid + 1, r, x, v);
    }

    a[u] = gcd(a[u << 1], a[u << 1 | 1]);
}

inline long long query(int u, int l, int r, int x, int y) {
    if (x <= l && r <= y) return a[u];

    int mid = (l + r) >> 1;
    if (y <= mid) return query(u << 1, l, mid, x, y);
    if (mid < x) return query(u << 1 | 1, mid + 1, r, x, y);

    return gcd(query(u << 1, l, mid, x, y), query(u << 1 | 1, mid+1, r, x, y));
}

int n, q;
int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
#endif

    read(n);
    for (int i = 1; i <= n; ++i) {
        long long x;
        read(x);
        modify(1, 1, n, i, x);
    }

    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        int op;
        long long x, y;

        read(op);
        read(x), read(y);

        if (op == 1) {
            modify(1, 1, n, x, y);
        } else {
            printf("%lld\n", query(1, 1, n, x, y));
        }
    }
    
    return 0;
}
