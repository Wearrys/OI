#include <bits/stdc++.h>
using namespace std;

const int N = 100000;

int n;
int a[N + 5], b[N + 5];
vector<pair<int, int> > val;
long long ans = LLONG_MAX, sa, sb;

int main() {

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d", a+i, b+i), sa += a[i], sb += b[i];
        val.emplace_back(a[i], i);
        val.emplace_back(b[i], i);
    }
    ans = min(sa, sb);

    std::sort(val.begin(), val.end());

    long long s0 = 0, s1 = 0, s2 = 0;
    for(int i = 0; i < n-2; ++i) {
        s0 += val[i].first; 
    }
    s1 = s0 + val[n-2].first;
    s2 = s1 + val[n-1].first;

    static int vis[N + 5];
    memset(vis, -1, sizeof vis);

    for(int i = 0; i < 2*n; ++i) {
        if(vis[val[i].second] >= 0) {
            int j = vis[val[i].second];
            if(i < n) ans = min(ans, s2);
            else if(j < n - 1) ans = min(ans, val[i].first + s1);
            else ans = min(ans, val[i].first + val[vis[val[i].second]].first + s0);
        } else vis[val[i].second] = i;
    }
    printf("%lld\n", ans);

    return 0;
}
