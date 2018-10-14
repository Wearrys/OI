#include <bits/stdc++.h>
using namespace std;

const int N = 100000;

int n, m;
long long ans;
char s[N + 5], t[N + 5];

int main() {

    scanf("%d%d%s%s", &n, &m, s, t);
    ans = 1ll * n * m / std::__gcd(n, m);

    for(int i = 0; i < n; ++i) if(1ll * i * m % n == 0) {
        int j = 1ll * i * m / n;

        if(s[i] != t[j]) {
            puts("-1");
            return 0;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
