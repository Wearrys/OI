#include <bits/stdc++.h>
using namespace std;

const int N = 100000;
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

char st[N + 5];
int l, n, m = 1;
int p[N + 5], a[N + 5], v[N + 5];

int calc(int all) {
    int res = 1;
    for(int i = 1; i <= n && res; ++i) {
        int tmp = 0, b = (1 << p[i]) - 1;
        for(int r = all; r; r >>= p[i]) tmp |= r & b;
        res = 1ll * res * (p[i] - __builtin_popcount(tmp)) % mo;
    }
    return res;
}

int ans;
void dfs(int u, int c, int sgn, int all) {
    if(u == l) {
        ans = (ans + 1ll * v[c] * sgn % mo * calc(all)) % mo;
        return;
    }

    if(st[u] == '1') {
        dfs(u + 1, c + 1, sgn, all | (1 << u));
    } else {
        dfs(u + 1, c, sgn, all);
        dfs(u + 1, c + 1, mo-sgn, all | (1 << u));
    }
}

int main() {

    scanf("%s%d", st, &n);

    l = strlen(st);
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d", p + i, a + i);
        m = 1ll * m * fpm(p[i], a[i] - 1) % mo;
    }

    std::sort(p + 1, p + n + 1);

    int t = n;
    while(n > 0 && p[n] >= l) -- n;

    for(int i = 0; i <= l; ++i) {
        v[i] = 1;
        for(int j = n + 1; j <= t; ++j) v[i] = 1ll * v[i] * (p[j] - i) % mo;
    }

    dfs(0, 0, 1, 0);
    printf("%lld\n", 1ll * ans * m % mo);

    return 0;
}
