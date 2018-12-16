#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100000;

int m;
ll n, x[N + 5];

int main() {
#ifdef Wearry 
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%lld%d", &n, &m);
    if(m == 1) return printf("%lld\n", n - 1), 0;
    for(int i = 0; i < m; ++i) scanf("%lld", x + i);

    sort(x, x + m);

    int u = 0;
    ll mx = x[0] + n - x[m - 1];
    for(int i = 1; i < m; ++i) if(x[i] - x[i-1] > mx) {
        u = i;
        mx = x[i] - x[i-1];
    }

    ll s = x[u];
    for(int i = 0; i < m; ++i) {
        x[i] -= s;
        if(x[i] < 0) x[i] += n;
    }

    rotate(x, x + u, x + m);
    x[m] = x[0];

    auto chk = [&] (ll len) {
        static ll f[N + 5][2];
        memset(f, ~0x3f, sizeof f);

        f[0][1] = 1;
        for(int i = 1; i < m; ++i) {
            f[i][0] = max(f[i][0], f[i-1][1]);
            if(f[i][0] >= x[i]) f[i][1] = max(f[i][1], x[i] + len + 1);
            if(f[i][0] >= x[i] - len) f[i][1] = max(f[i][1], x[i] + 1);
            if(f[i][0] >= x[i+1] - len) f[i+1][1] = max(f[i+1][1], x[i] + len + 1);
        }
        if(f[m-1][1] >= n - len) return true;

        memset(f, ~0x3f, sizeof f);

        f[1][1] = max(len + 1, x[1] + 1);
        for(int i = 2; i < m; ++i) {
            f[i][0] = max(f[i][0], f[i-1][1]);
            if(f[i][0] >= x[i]) f[i][1] = max(f[i][1], x[i] + len + 1);
            if(f[i][0] >= x[i] - len) f[i][1] = max(f[i][1], x[i] + 1);
            if(f[i][0] >= x[i+1] - len) f[i+1][1] = max(f[i+1][1], x[i] + len + 1);
        }
        if(f[m-1][1] >= n + x[1] - len) return true;
        return false;
    };

    ll l = 0, r = mx;
    while(l < r) {
        ll mid = (l + r) >> 1;
        if(chk(mid)) r = mid; else l = mid + 1;
    }
    printf("%lld\n", l);

    return 0;
}
