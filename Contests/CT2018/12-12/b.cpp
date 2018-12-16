#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 15;
const int mo = 998244353;

#define lg2(x) (63 - __builtin_clzll(x))

int dfs(vector<ll> lim, ll c) {
    int u = max_element(lim.begin(), lim.end()) - lim.begin();

    if(lim[u] == 0) return c == 0;
    if(lg2(lim[u]) < lg2(c)) return 0;
    
    int g[2], h[2]; 
    int s = lg2(lim[u]);

    g[0] = 1, g[1] = 0;
    for(int i = 0; i < (int) lim.size(); ++i) if(i != u) {
        h[0] = h[1] = 0;
        ll temp = lim[i] & ((1ll << (s + 1)) - 1);

        if(temp >> s & 1) {
            h[0] = ((1ll << s) % mo * g[0] + (temp - (1ll << s) + 1) % mo * g[1]) % mo;
            h[1] = ((1ll << s) % mo * g[1] + (temp - (1ll << s) + 1) % mo * g[0]) % mo;
        } else {
            h[0] = (temp + 1) % mo * g[0] % mo;
            h[1] = (temp + 1) % mo * g[1] % mo;
        }
        g[0] = h[0], g[1] = h[1];
    }

    bool flag = (lg2(c) == s);
    c ^= 1ll << s;
    lim[u] ^= 1ll << s;
    return (g[flag] + dfs(lim, c)) % mo;
}

ll l[N + 5], c;

int n, m;
int pw[N + 5]; 
int f[1 << N], sts[1 << N], val[1 << N], e[N + 5];

void input() {
    pw[0] = 1;
    for(int i = 1; i <= N; ++i) pw[i] = 3 * pw[i-1];

    scanf("%d%d%lld", &n, &m, &c);
    for(int i = 0; i < n; ++i) scanf("%lld", l + i);
    for(int i = 1; i < (1 << n); ++i) {
        int mn = -1;
        vector<ll> temp;
        for(int j = 0; j < n; ++j) if(i >> j & 1) {
            sts[i] += pw[j];
            temp.push_back(l[j]);
            if(!~mn || l[j] < l[mn]) mn = j;
        }

        f[i] = dfs(temp, c);
        if(__builtin_popcount(i) & 1) {
            val[i] = 1;
            sts[i] += pw[mn];
        } else {
            val[i] = (l[mn] + 1) % mo;
        }
    }

    f[0] = (c == 0);

    for(int i = 0; i < m; ++i) {
        static int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        e[u] |= 1 << v, e[v] |= 1 << u;
    }
}

int dp[15000005], coe[1 << N], ept[1 << N];

void solve() {
    ept[0] = coe[0] = 1;
    for(int i = 1; i < (1 << n); ++i) {
        int u = __builtin_ctz(i), res = i ^ (1 << u);
        coe[i] = ept[i] = ept[res] & ((e[u] & res) == 0);

        if(res > 0) {
            for(int j = (res - 1) & res; ; j = (j - 1) & res) {
                coe[i] = (coe[i] - 1ll * coe[j ^ (1 << u)] * ept[res ^ j]) % mo;
                if(j == 0) break; 
            }
        }
    }

    int ans = 0;

    dp[0] = 1;
    for(int i = 0; i < pw[n]; ++i) if(dp[i]) {
        int res = 0;
        for(int j = 0; j < n; ++j) if((i / pw[j]) % 3 == 0) { res |= 1 << j; }

        if(res) {
            int u = __builtin_ctz(res); res ^= (1 << u);
            for(int j = res; ; j = (j - 1) & res) {
                int k = j ^ (1 << u);
                dp[i+sts[k]] = (dp[i+sts[k]] + 1ll * dp[i] * val[k] % mo * coe[k]) % mo;
                if(j == 0) break;
            }
        } else {
            for(int j = 0; j < n; ++j) if((i / pw[j]) % 3 == 2) { res |= 1 << j; }
            ans = (ans + 1ll * f[res] * dp[i]) % mo;
        }
    }
    printf("%d\n", (ans + mo) % mo);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    input();
    solve();

    return 0;
}
