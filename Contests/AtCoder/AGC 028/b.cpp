#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100000;
const int mo = 1e9 + 7;

int n;
int a[N + 5], s[N + 5];
int fac[N + 5], inv[N + 5];

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = (ll) res * x % mo;
        x = (ll) x * x % mo;
    }
    return res;
}

void init() {
    fac[0] = 1;
    for(int i = 1; i <= N; ++i) fac[i] = (ll) fac[i-1] * i % mo;
    inv[N] = fpm(fac[N], mo - 2);
    for(int i = N; i >= 1; --i) inv[i-1] = (ll) inv[i] * i % mo;
}

int ans = 0;
int main() {
    init();
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        s[i-1] = (s[i-1] + a[i]) % mo;
        s[n-i] = (s[n-i] + a[i]) % mo;
        ans = (ans + 1ll * fac[n] * a[i]) % mo;
    }
    for(int k = n - 1; k >= 1; --k) {
        s[k] = (s[k] + s[k+1]) % mo;
        ans = (ans + 1ll * s[k] * fac[n] % mo * inv[k + 1] % mo * fac[k]) % mo;
    }
    printf("%d\n", ans);
    return 0;
}
