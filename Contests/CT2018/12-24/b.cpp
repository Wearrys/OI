#include <bits/stdc++.h>
using namespace std;

const int K = 100;
const int N = 1000000;
const int mo = 19491001;

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = 1ll * res * x % mo;
        x = 1ll * x * x % mo;
    }
    return res;
}

int n, k, d;

int main() {

    cin >> n >> k >> d;

    static int fac[N + 5], inv[N + 5];

    fac[0] = 1;
    for(int i = 1; i <= N; ++i) fac[i] = 1ll * fac[i-1] * i % mo;
    inv[N] = fpm(fac[N], mo - 2);
    for(int i = N; i >= 1; --i) inv[i-1] = 1ll * inv[i] * i % mo;

    if(d == 1) {
        printf("%d\n", fpm(k, n));
    } else if(d == 2) {

        int ans = 0;
        for(int i = 0; i <= k; ++i) 
            ans = (ans + 1ll * fac[k] * inv[k-i] % mo * inv[i] % mo * fpm(k - 2 * i, n)) % mo;
        ans = 1ll * ans * fpm((mo + 1) / 2, k) % mo;

        printf("%d\n", ans);
    } else {

        const int x = 663067;

        int ans = 0;
        for(int i = 0; i <= k; ++i) {
            for(int j = 0; i + j <= k; ++j) {
                ans = (ans + 1ll * fac[k] * inv[i] % mo * inv[j] % mo * inv[k - i - j] % mo * fpm((i + 1ll * j * x % mo + 1ll * (k - i - j) * x % mo * x % mo) % mo, n)) % mo;
            }
        }
        ans = 1ll * ans * fpm(fpm(3, mo - 2), k) % mo;

        printf("%d\n", ans);
    }

    return 0;
}
