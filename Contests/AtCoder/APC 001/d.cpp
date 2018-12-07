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

int fa[N + 5];
int find(int x) {
    return (fa[x] == x) ? x : fa[x] = find(fa[x]);
}

int a[N + 5], n, m;
vector<int> v[N + 5], all;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(m);
    for(int i = 0; i < n; ++i) fa[i] = i;
    for(int i = 0; i < n; ++i) read(a[i]);
    for(int i = 0; i < m; ++i) {
        static int x, y;
        read(x), read(y);
        fa[find(x)] = find(y);
    }

    int c = 0;
    ll ans = 0;

    for(int i = 0; i < n; ++i) {
        v[find(i)].pb(a[i]);
        if(find(i) == i) ++ c;
    }
    if(c == 1) return !puts("0");

    for(int i = 0; i < n; ++i) if(find(i) == i) {
        std::sort(v[i].begin(), v[i].end());

        ans += v[i][0];
        for(int j = 1; j < (int) v[i].size(); ++j) { all.pb(v[i][j]); }
    }

    if((int) all.size() < c - 2) {
        puts("Impossible");
    } else {
        std::sort(all.begin(), all.end());
        for(int i = 0; i < c - 2; ++i) ans += all[i];
        printf("%lld\n", ans);
    }

    return 0;
}
