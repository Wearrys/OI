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

const int N = 300000;

typedef unsigned int uint;

uint n, ans;
uint a, b, c, d;

uint f(uint x) {
    return d + x * (c + x * (b + x * a));
}

uint calc(uint p) {
    uint m = n, res = 0;
    while(m) {
        res += m / p;
        m /= p;
    }
    return res * f(p);
}

uint pri[N + 5];
uint vis[N + 5], now;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    read(a), read(b), read(c), read(d);

    ++ now;
    for(uint i = 2; i <= N; ++i) if(vis[i] != now) {
        ans += calc(i);
        pri[++ pri[0]] = i;
        for(uint j = i; j <= N / i; j++) vis[i * j] = now;
    }

    for(uint i = N + 1; i <= n; i += N) {
        ++ now;
        uint l = i, r = std::min(i + N - 1, n);

        for(uint j = 1; j <= pri[0]; ++j) {
            uint p = pri[j];
            for(uint k = (l + p - 1) / p * p; k <= r; k += p) vis[k - l] = now;
        }
        for(uint j = l; j <= r; ++j) if(vis[j - l] != now) ans += calc(j);
    }
    printf("%u\n", ans);

    return 0;
}
