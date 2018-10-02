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

struct node {
    ll d;
    int id; 

    bool operator < (const node& rhs) const {
        return d > rhs.d;
    }
};

int n;
node t[N + 5];
int fa[N + 5], sz[N + 5];
std::map <ll, int> mp;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    for(int i = 1; i <= n; ++i) {
        read(t[i].d), t[i].id = i;
    }

    std::sort(t + 1, t + n + 1);

    for(int i = 1; i <= n; ++i) mp[t[i].d] = i;
    for(int i = 1; i < n; ++i) {
        ++ sz[i];
        fa[i] = mp[t[i].d - n + 2 * sz[i]];
        if(!fa[i]) return !puts("-1");
        sz[fa[i]] += sz[i];
        t[n].d -= sz[i];
    }

    if(t[n].d) return !puts("-1");

    for(int i = 1; i < n; ++i) {
        printf("%d %d\n", t[i].id, t[fa[i]].id);
    }

    return 0;
}
