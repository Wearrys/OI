#include <bits/stdc++.h>

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

const int oo = 0x3f3f3f3f;

string procStatus() {
    std::ifstream t("/proc/self/status");
    return string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}

template <typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = 100000;

ll a[N + 5];
int n, s, t;
int x[N + 5];

int lg[N + 5];
int mx[22][N + 5], mn[22][N + 5];

inline int _max(int p, int q) { return a[p] > a[q] ? p : q; }
inline int _min(int p, int q) { return a[p] < a[q] ? p : q; }

inline int get_mn(int l, int r) {
    int k = lg[r - l + 1];
    return _min(mn[k][l], mn[k][r - (1 << k) + 1]);
}

inline int get_mx(int l, int r) {
    int k = lg[r - l + 1];
    return _max(mx[k][l], mx[k][r - (1 << k) + 1]);
}

bool chk(const int& S) {
    for(int i = 1; i <= n; ++i) {
        a[i] = x[i] - 2ll * S * t * i;
        mx[0][i] = mn[0][i] = i;
    }

    for(int j = 1; j < 17; ++j) {
        for(int i = 1; i + (1 << (j-1)) <= n; ++i) {
            mx[j][i] = _max(mx[j-1][i], mx[j-1][i + (1 << (j-1))]);
            mn[j][i] = _min(mn[j-1][i], mn[j-1][i + (1 << (j-1))]);
        }
    }

    int l, r;
    static int stk[N + 5], top;
    static int pre[N + 5], nxt[N + 5];

    top = 0;
    for(int i = 1; i <= n; ++i) {
        while(top && a[stk[top-1]] <= a[i]) -- top;
        pre[i] = stk[top-1]; stk[top ++] = i;
    }

    top = 0;
    for(int i = n; i >= 1; --i) {
        while(top && a[stk[top-1]] >= a[i]) -- top;
        nxt[i] = stk[top-1]; stk[top ++] = i;
    }

    for(l = r = s; 1 < l || r < n; ) {

        bool flag = false;
        int p = pre[l], q = nxt[r];
        if(p && a[get_mn(p, l)] >= a[r]) l = p, flag = true;
        if(q && a[get_mx(r, q)] <= a[l]) r = q, flag = true;

        if(!flag) {
            if(l == 1) return a[get_mx(r, n)] <= a[l];
            if(r == n) return a[get_mn(1, l)] >= a[r];

            p = get_mn(1, l);
            q = get_mx(r, n);

            if(a[p] < a[r] || a[q] > a[l]) return false;

            int tp = get_mx(1, p), tq = get_mn(q, n);

            if(a[tp] >= a[q]) l = tp; 
            else if(a[tq] <= a[p]) r = tq;
            else return false;
        }
    }
    return true;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(s), read(t);
    for(int i = 1; i <= n; ++i) read(x[i]);
    for(int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;

    int l = 0, r = x[n] / t / 2;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(chk(mid)) r = mid; else l = mid + 1;
    }
    printf("%d\n", l);

    return 0;
}
