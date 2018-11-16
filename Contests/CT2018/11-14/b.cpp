#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100000;
const ll RNG = (ll) 2e9;
const ll OO = 0x3f3f3f3f3f3f3f3fll;

template <typename T>
inline void chkmax(T&a, T b) {
    a = (b > a) ? b : a;
}

struct func {
    ll k, b;
    func(ll _k = 0, ll _b = -OO): k(_k), b(_b) { }

    inline ll val(ll x) { return k * x + b; }
};

#define mid ((l + r) >> 1)

struct seg_t {
    func f;
    seg_t *lc, *rc;

    void modify(ll l, ll r, func v) {
        if(v.val(mid) > f.val(mid)) { std::swap(v, f); }
        if(l == r || (v.k == 0 && v.b == -OO)) return;

        (v.val(l) < f.val(l)) ? 
            (rc ? rc : rc = new seg_t) -> modify(mid+1, r, v) : 
            (lc ? lc : lc = new seg_t) -> modify(l, mid, v);
    }

    ll query(ll l, ll r, ll x) {
        if(l == r) return f.val(x);
        return max(f.val(x), 
                (x <= mid) ? (lc ? lc -> query(l, mid, x) : -OO) : (rc ? rc -> query(mid+1, r, x) : -OO));
    }
};

seg_t s0, s1;

int n;
int f[N + 5];
ll A[N + 5], B[N + 5];
int l[N + 5], r[N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d", l + i, r + i);
        l[i] *= 2, r[i] *= 2;
        B[i] = B[i-1] + (r[i] - l[i]);
        A[i] = A[i-1] + (r[i] + l[i]) / 2 * (r[i] - l[i]);
    }
    
    int lst = n, ans = 1;
    for(int i = n-1; i >= 1; --i) {
        s0.modify(1, RNG, func(+r[i + 1], A[i] - B[i] * r[i+1]));
        s1.modify(1, RNG, func(-l[i + 1], B[i] * l[i+1] - A[i]));
        if((s0.query(1, RNG, B[i-1]) <= A[i-1] && s1.query(1, RNG, B[i-1]) <= -A[i-1])) { chkmax(ans, lst - i), lst = i; }
    }

    chkmax(ans, lst - 1);
    printf("%d\n", ans);

    return 0;
}
