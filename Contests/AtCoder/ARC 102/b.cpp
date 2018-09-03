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

int l;
int n = 20, m;

struct edge {
    int u, v, w;
};

edge e[1000];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    for(int i = 19, j = 1; i > 1; --i) {
        e[++ m] = (edge) { i, i + 1, 0 };
        e[++ m] = (edge) { i, i + 1, j };
        j <<= 1;
    }

    read(l);
    int cur = 0;
    if(l >> 19 & 1) {
        cur |= (1 << 19);
        e[++ m] = (edge) { 1, 2, 1 << 18 };
        e[++ m] = (edge) { 1, 2, 0 };
    }

    for(int i = 18; i >= 0; --i) if(l >> i & 1) {
        e[++ m] = (edge) { 1, 19-i+1, cur };
        cur |= (1 << i);
    }

    printf("%d %d\n", n, m);
    for(int i = 1; i <= m; ++i) printf("%d %d %d\n", e[i].u, e[i].v, e[i].w);

    return 0;
}
