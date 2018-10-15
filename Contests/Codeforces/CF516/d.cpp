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

inline ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (!b) { x = 1; y = 0; return a; }
	ll g = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return g;
}

ll n, k, l, r;
ll len, ans = -1;

void calc(ll t, ll c, ll L, ll R, bool f = 0) {
    if(!c) return;
    static ll x, y;
    exgcd(c, 1ll, x, y);
    x *= t, y *= t;

    if(y < f) { x -= ((f-y+c-1)/c); y = y + ((f-y+c-1) / c) * c; }
    if(x <= L) { y = y - (L - x) * c; x = L; }
    if(y < f) return;

    ll lim = R - L;
    chkmin(lim, (y-f) / c);
    chkmin(lim, (n - len - x + y) / (c + 1));

    if(lim < 0) return;

    y = y - lim * c;
    x = x + lim;

    if(y <= len && (x-y) <= n-len && x >= y) chkmax(ans, x);
}

void solve(ll c, ll x, ll y) {
    if(c == 0 && k >= len) {
        if(k - len <= len) chkmax(ans, k - len + n - len);
        if(k - len + 1 <= len) chkmax(ans, k - len + 1 + n - len);
    }
    if(x > 2*n || y < n) return;
    x = std::max(x - n, 0ll);
    y = std::min(y - n, n);

    ll t = k - c * n - len;
    calc(t, c, x, y);
    calc(t + 1, c, x, y, 1);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    std::cin >> n >> l >> r >> k;

    if(l <= r) {
        len = r - l + 1;
    } else {
        len = r - l + 1 + n;
    }

    for(ll t = 1, nxt; t <= k; t = nxt + 1) {
        nxt = k / (k / t);
        solve(k / t, t, nxt);
        solve(k / t - 1, t, nxt);
    }

    printf("%lld\n", ans);
    return 0;
}
