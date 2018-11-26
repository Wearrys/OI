#include <bits/stdc++.h>
using namespace std;

const int N = 100;

void chkmin(int&a, int b) {
    (a > b) ? a = b : 0;
}

int n;
long long a[N + 5], r[N + 5];
vector<long long> dis[N + 5];

int fa[N + 5];
int findset(int x) {
    return (fa[x] == x) ? fa[x] : fa[x] = findset(fa[x]);
}

int ans = 0x3f3f3f3f;
void dfs(int cur, int cnt = 0) {
    if(cnt + (n - cur + 1) >= ans) return;
    if(cur > n) {
        for(int i = 1; i <= n; ++i) fa[i] = i;
        for(int i = 1; i <= n; ++i) {
            for(int j = i+1; j <= n; ++j) if(min(r[i], r[j]) >= abs(a[i] - a[j])) {
                fa[findset(i)] = findset(j);
            }
        }
        for(int i = 1; i <= n; ++i) if(findset(i) != findset(1)) return;
        ans = cnt; 
        return;
    }

    for(int i = 0; i < (int) dis[cur].size(); ++i) {
        r[cur] = dis[cur][i];
        int _cnt = cnt;
        for(int j = 1; j <= n; ++j) _cnt += (r[cur] >= abs(a[cur] - a[j]));
        dfs(cur + 1, _cnt);
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%lld", a + i);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) dis[i].push_back(abs(a[i] - a[j]));
        sort(dis[i].begin(), dis[i].end());
        dis[i].erase(unique(dis[i].begin(), dis[i].end()), dis[i].end());
        reverse(dis[i].begin(), dis[i].end());
    }

    dfs(1);
    printf("%d\n", ans);

    return 0;
}
