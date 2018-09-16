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

const int N = 200000;

int n, x;
ll s[N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(x);
    for(int i = 1; i <= n; ++i) {
        read(s[i]), s[i] += s[i-1];
    }

    ll ans = (ll) 1e18;
    for(int i = 1; i <= n; ++i) {
        ll res = 1ll * (i + n) * x;

        int cost = 5;
        for(int j = n; j >= 1 && res < ans; j -= i) {
            int lst = std::max(j-i, 0);
            res = res + 1ll * cost * (s[j] - s[lst]);
            if(j != n) cost += 2;
        }
        chkmin(ans, res);
    }
    printf("%lld\n", ans);

    return 0;
}
