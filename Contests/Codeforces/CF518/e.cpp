#include <bits/stdc++.h>
using namespace std;

const int N = 500000;
const int mo = 998244353;

typedef long long ll;

int n;
int dp[N + 5][2];
vector<int> G[N + 5];

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = (ll) res * x % mo;
        x = (ll) x * x % mo;
    }
    return res;
}

int ans;
int dfs(int u, int f = 0) {
    int sz = 1;
    dp[u][0] = 1;

    for(auto v : G[u]) {
        if(v == f) continue;
        sz += dfs(v, u);

        dp[u][1] = ((ll) dp[u][1] * (dp[v][0] + dp[v][1]) % mo + (ll) dp[u][0] * dp[v][0]) % mo;
        dp[u][0] = (ll) dp[u][0] * dp[v][1] % mo;
    }

    ans = (ans + (ll) fpm(2, n-sz+1) * dp[u][1]) % mo;
    dp[u][1] = (dp[u][1] * 2 % mo + dp[u][0]) % mo;
    return sz;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i < n; ++i) {
        static int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs(1);
    printf("%d\n", ans);

    return 0;
}
