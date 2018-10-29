#include <bits/stdc++.h>
using namespace std;

const int N = 200000;

typedef long long ll;

int n;
int a[N + 5], b[N + 5];

ll ans = -1;
ll cost() {
    ll res = 0;
    for(int i = 1; i < n; ++i) {
        res += std::abs(b[i] - b[i-1]);
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", a + i);
    std::sort(a, a + n);

    if(n & 1) {
        int j = n-1;
        for(int i = 2; i < n - 1; i += 2, -- j) { b[i] = a[j]; }
        b[0] = a[j--];
        b[n-1] = a[j--];
        for(int i = 1; i < n; i += 2, -- j) { b[i] = a[j]; }
        ans = max(ans, cost());

        j = n - 1;
        for(int i = 1; i < n; i += 2, -- j) { b[i] = a[j]; }
        b[0] = a[j--];
        b[n-1] = a[j--];
        for(int i = 2; i < n - 1; i += 2, -- j) { b[i] = a[j]; }

        ans = max(ans, cost());
    } else {
        int j = n-1;
        for(int i = 1; i < n; i += 2, -- j) { b[i] = a[j]; }
        for(int i = 0; i < n; i += 2, -- j) { b[i] = a[j]; }

        ans = max(ans, cost());
    }
    printf("%lld\n", ans);
    return 0;
}
