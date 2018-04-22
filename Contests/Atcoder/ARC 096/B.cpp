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

int n;
ll c, ans;
ll x[N + 5], v[N + 5];
ll t0[N + 5], t1[N + 5];
ll pre[N + 5], suf[N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(c);
    for(int i = 1; i <= n; ++i) { read(x[i]), read(v[i]); }
    for(int i = 1; i <= n; ++i) {
        pre[i] = pre[i-1] + v[i];
        chkmax(ans, pre[i] - x[i]);
        t0[i] = std::max(t0[i-1], pre[i] - 2 * x[i]);
    }
    for(int i = n; i >= 1; --i) {
        suf[i] = suf[i+1] + v[i];
        chkmax(ans, suf[i] - (c - x[i]));
        t1[i] = std::max(t1[i+1], suf[i] - 2 * (c - x[i]));
    }

    for(int i = 1; i <= n; ++i) {
        chkmax(ans, pre[i] + t1[i + 1] - x[i]);
        chkmax(ans, suf[i] + t0[i - 1] - (c - x[i]));
    }

    printf("%lld\n", ans);

    return 0;
}
