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

template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;

template<typename T> T read(T& x) {
    T f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = 1000000;
const int mo = 1e9 + 7;

int n;
ll s[N + 5];
int f[N + 5], g[N + 5];
int w[N + 5], p[N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    for(int i = 1; i <= n; ++i) read(w[i]);
    for(int i = 2; i <= n; ++i) read(p[i]);
    for(int i = n; i >= 1; --i) {
        s[i] += w[i];
        if(p[i]) s[p[i]] += s[i];
    }

    for(int i = 1; i <= n; ++i) {
        ll temp = std::__gcd(s[1], s[i]);
        if(s[1] / temp <= n) ++ f[s[1] / temp];
    }

    for(int i = n; i >= 1; --i) {
        for(int j = i << 1; j <= n; j += i) f[j] += f[i];
    }

    for(int i = n; i >= 1; --i) if(f[i] == i) {
        g[i] = 1;
        for(int j = i << 1; j <= n; j += i) g[i] = (g[i] + g[j]) % mo;
    }
    printf("%d\n", g[1]);

    return 0;
}
