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

const int N = 500000;
const int mo = 998244353;

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = 1ll * res * x % mo;
        x = 1ll * x * x % mo;
    }
    return res;
}

int n, m, l, len, rt;
vector<int> G[N + 5], R;

int dep[N + 5], tot[N + 5];
void dfs(int u, int f) {
    dep[u] = 0, tot[u] = 1;
    for(auto v : G[u]) {
        if(v == f) continue;

        dfs(v, u);

        if(dep[v] + 1 > dep[u]) {
            dep[u] = dep[v] + 1;
            tot[u] = tot[v];
        } else if (dep[v] + 1 == dep[u]) {
            tot[u] += tot[v];
        }
    }
}

int dis[N + 5], pre[N + 5];
int bfs(int s) {
    int t;
    std::queue<int> q;
    memset(dis, oo, sizeof dis);

    q.push(s);
    pre[s] = dis[s] = 0;

    while(!q.empty()) {
        int x = q.front(); q.pop();

        t = x;
        for(auto y : G[x]) {
            if(chkmin(dis[y], dis[x] + 1)) {
                pre[y] = x, q.push(y);
            }
        }
    }
    return t;
}

int inv[N + 5], h[N + 5];
int fac[N + 5], ifac[N + 5];

void init() {
    h[1] = 1;
    inv[0] = inv[1] = 1;
    for(int i = 2; i <= N; ++i) {
        inv[i] = 1ll * (mo - mo / i) * inv[mo % i] % mo;
        h[i] = (h[i-1] + inv[i]) % mo;
    }

    fac[0] = 1;
    for(int i = 1; i <= N; ++i) fac[i] = 1ll * fac[i-1] * i % mo;
    ifac[N] = fpm(fac[N], mo - 2);
    for(int i = N; i >= 1; --i) ifac[i-1] = 1ll * ifac[i] * i % mo;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    init();

    read(n);
    for(int i = 1; i < n; ++i) {
        static int u, v;
        read(u), read(v);
        G[u].pb(v), G[v].pb(u);
    }
    for(int i = 1; i <= n; ++i) m += (G[i].size() == 1);

    int s = 1, t;
    s = bfs(s), t = bfs(s);

    for(int i = t; i; i = pre[i]) {
        R.pb(i);
    }

    len = dis[t], rt = R[len / 2];

    dfs(rt, 0);

    vector<int> S;
    for(auto v : G[rt]) {
        if(len & 1) {
            if(S.empty()) S.resize(2);

            if(dep[v] == dep[rt] - 1) {
                S[0] += tot[v];
            } 
            if(dep[v] == dep[rt] - 2) {
                S[1] += tot[v];
            }
        } else {
            if(dep[v] == dep[rt] - 1) {
                S.pb(tot[v]);
            }
        }
    }

    int ans = 0;

    for(auto k : S) { l += k; }
    for(auto k : S) {
        for(int i = 1; i <= k; ++i) {
            ans = (ans + 1ll * fac[l-k] * fac[l-i-1] % mo * ifac[l-k-1] % mo * fac[k] % mo * ifac[k-i] % mo * (mo + h[l] - h[i])) % mo;
        }
    }
    ans = 1ll * ans * m % mo;
    ans = 1ll * ans * ifac[l] % mo;
    printf("%d\n", ans);

    return 0;
}
