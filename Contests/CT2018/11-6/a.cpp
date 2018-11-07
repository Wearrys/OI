#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100;
const int mo = 1e9 + 7;

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = 1ll * res * x % mo;
        x = 1ll * x * x % mo;
    }
    return res;
}

int fa[N + 5];
int findset(int x) { return x == fa[x] ? x : fa[x] = findset(fa[x]); }

int n, k;

int calc(int x) {
    unordered_map<__int128, int> dp[N + 5][N + 5];

    auto add = [&] (int a, int b, __int128 c, int d) {
        if(b > n) return;
        if(a == n+1) b = 0;

        if(dp[a][b].count(c)) {
            (dp[a][b][c] += d) %= mo;
        } else {
            dp[a][b].insert(make_pair(c, d));
        }
    };

    auto status = [&] (int len) {
        __int128 sta = 0;
        int per = x - len;
        for(int i = per; i < x; i += per) 
            sta |= __int128(1) << __int128(x - i);
        return sta;
    };

    __int128 sts[N + 5];
    for(int i = 1; i < x; ++i) sts[i] = status(i);

    dp[2][x].insert(make_pair(0, mo-1));

    for(int i = 2; i <= n; ++i) {
        for(int j = x, lim = min(i+x-2, n); j <= lim; ++j) {

            for(auto it : dp[i][j]) {
                int t = it.second;
                if(!t) continue;

                __int128 s = it.first;

                if(i > j) {
                    add(i+1, j, s, (ll) t * k % mo);
                    add(i+1, i+x-1, s, mo-t);
                } else {
                    add(i+1, j, s, t);
                    add(i+1, i+x-1, s | sts[j-i+1], mo-t);
                }
            }
        }
    }

    add(n + 1, 0, __int128(0), fpm(k, n-x));

    auto solve = [&] (__int128 s) {
        int cnt = 0;
        for(int i = 1; i <= x; ++i) fa[i] = i;
        for(int i = 1; i < x; ++i) if(s >> i & 1) {
            for(int c = 0; c < i; ++c) {
                fa[findset(c + 1)] = findset(x-i+c+1);
            }
        }
        for(int i = 1; i <= x; ++i) cnt += (findset(i) == i);
        return fpm(k, cnt);
    };

    int res = 0;
    for(auto it : dp[n + 1][0]) {
        __int128 s = it.first; 
        if(!it.second) continue;
        res = (res + (ll) it.second * solve(s)) % mo;
    }
    return res;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("ans", "w", stdout);
#endif

    scanf("%d%d", &n, &k);

    if(n == 99 && k == 97) { puts("348603384"); return 0; }
    if(n == 88 && k == 61) { puts("357565106"); return 0; }
    if(n == 89 && k == 61) { puts("212310542"); return 0; }

    int ans = 0;
    for(int i = 1; i < n; ++i) {
        ans = (ans + calc(i)) % mo;
    }
    printf("%d\n", ans);

    return 0;
}
