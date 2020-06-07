#include <bits/stdc++.h>
using namespace std;

const int N = 200000;

int n;
int x[N + 5], y[N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
#endif

    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", x + i, y + i);
    }

    sort(x+1, x+n+1);
    sort(y+1, y+n+1);

    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += abs(x[i] - i) + abs(y[i] - i);
    }

    printf("%lld\n", ans);

    return 0;
}
