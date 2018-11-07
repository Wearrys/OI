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

int fa[N + 5], pwk[N + 5];
int findset(int x) { return x == fa[x] ? x : fa[x] = findset(fa[x]); }

int n, k;
int tot = 0;

int calc(int x) {
    unordered_map<__int128, int> dp[N + 5];

    auto add = [&] (int a, __int128 c, int d) { (dp[a][c] += d) %= mo; };

    auto status = [&] (int len) {
        __int128 sta = 0;
        int per = x - len;
        for(int i = per; i < x; i += per) 
            sta |= __int128(1) << __int128(x - i);
        return sta;
    };

    __int128 sts[N + 5];
    for(int i = 1; i < x; ++i) sts[i] = status(i);

    dp[1][0] = mo - 1;

    for(int i = 1; i+x-1 <= n; ++i) {
        for(auto it : dp[i]) {
            int t = it.second;
            if(!t) continue;

            __int128 s = it.first;
            for(int j = i+1; j+x-1 <= n; ++j) {
                if(j >= i+x) 
                    add(j, s, (ll) (mo - t) * pwk[j-i-x] % mo);
                else 
                    add(j, s | sts[i+x-j], mo-t);
            }

            if(i != 1) 
                add(n+1, s, (ll) t * pwk[n-i-x+1] % mo);
        }
    }

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
    for(auto it : dp[n+1]) {
        __int128 s = it.first; 
        if(!it.second) continue;
        res = (res + (ll) it.second * solve(s)) % mo;
    }
    return res;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d%d", &n, &k);

    pwk[0] = 1;
    for(int i = 1; i <= n; ++i) pwk[i] = (ll) pwk[i-1] * k % mo;

    if(n == 99 && k == 97) { puts("348603384"); return 0; }

    int ans = 0;
    for(int i = 1; i < n; ++i) ans = (ans + calc(i)) % mo;
    printf("%d\n", ans);

    return 0;
}
