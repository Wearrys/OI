#include <bits/stdc++.h>
using namespace std;

const int N = 300000;

int n;
long long a[N + 5], d[N + 5];

int main() {
#ifdef Wearry 
    freopen("in", "r", stdin);
#endif

    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        a[i] = 1;
    }

    for (int i = 1; i < n; ++i) {
        scanf("%lld", d + i);

        a[i] = a[i] / __gcd(a[i], d[i]) * d[i];
        a[i+1] = a[i+1] / __gcd(a[i+1], d[i]) * d[i];
    }

    for (int i = 1; i < n; ++i) {
        if (__gcd(a[i], a[i+1]) != d[i]) {
            puts("-1");
            return 0;
        }
    }
    for (int i = 1; i <= n; ++i) printf("%lld ", a[i]);
    return 0;
}
