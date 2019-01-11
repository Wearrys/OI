#include <bits/stdc++.h>
using namespace std;

const int N = 10000000;
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

bool notprime[N + 5];
int prime[N + 5], pcnt;
int phi[N + 5], mu[N + 5], mn[N + 5];

void sieve() {
    phi[1] = mu[1] = 1;
    for(int i = 2; i <= N; ++i) {
        if(!notprime[i]) {
            mu[i] = -1;
            mn[i] = i;
            phi[i] = i - 1;
            prime[pcnt ++] = i;
        }
        for(int j = 0; i * prime[j] <= N; ++j) {
            notprime[i * prime[j]] = true;

            if(i % prime[j] == 0) {
                mn[i * prime[j]] = mn[i] * prime[j];
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }

            mu[i * prime[j]] = -mu[i];
            mn[i * prime[j]] = prime[j];
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}

int n, k;
int main() {

    sieve();
    cin >> n >> k;

    static int s[N + 5], f[N + 5];

    f[1] = 1;
    for(int i = 0; i < pcnt; ++i) {
        int p = prime[i];
        for(long long j = p, c = 1; j <= N; j *= p, ++ c) {
            for(int x = 1, l = 0; l <= c; x *= p, ++ l) {
                s[x] = 0;
                for(int y = 1, e = 0; e <= l; y *= p, ++ e) {
                    s[x] = (s[x] + phi[j / y]) % mo;
                } s[x] = fpm(s[x], k);

                int sum = 0;
                for(int y = 1, e = 0; e <= l; y *= p, ++ e) {
                    sum = (sum + mu[x / y] * s[y]) % mo;
                }
                f[j] = (f[j] + 1ll * x * sum) % mo;
            }
        }
    }

    int ans = 1;
    for(int i = 2; i <= n; ++i) ans = (ans + (f[i] = 1ll * f[i / mn[i]] * f[mn[i]] % mo)) % mo;
    printf("%d\n", (ans + mo) % mo);

    return 0;
}
