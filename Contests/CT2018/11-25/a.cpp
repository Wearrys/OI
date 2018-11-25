#include <bits/stdc++.h>
using namespace std;

const int N = 100000;

#define fst first 
#define snd second
#define mp make_pair

int lg[N + 5];
long long mn[N + 5][21];
long long f[N + 5], w[N + 5];

long long query(int l, int r) {
    int k = lg[r - l + 1];
    return min(mn[r][k], mn[l + (1 << k) - 1][k]);
}

int n;
int l[N + 5], t[N + 5];

void input() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d%d%lld", l + i, t + i, w + i);
    for(int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
    for(int i = n-1; i >= 1; --i) w[i] += w[i + 1];
}

void solve() {
    memset(f, 0x3f, sizeof f);

    f[0] = 0;
    mn[0][0] = f[0];

    static int stk[N + 5], top = 0;

    stk[top ++] = -1;
    stk[top ++] = 0;

    for(int i = 1; i <= n; ++i) {
        while(top > 1 && t[stk[top-1]] <= t[i]) -- top;
        stk[top ++] = i;

        int j = top-1;
        for(; j >= 1 && stk[j-1] > l[i]; --j) 
            f[i] = min(f[i], query(stk[j-1], stk[j] - 1) + t[stk[j]] * w[i + 1]);
        f[i] = min(f[i], query(l[i], stk[j] - 1) + t[stk[j]] * w[i + 1]);

        mn[i][0] = f[i];
        for(j = 1; j <= 20 && (i >= (1 << j) - 1); ++j) {
            mn[i][j] = min(mn[i][j-1], mn[i - (1 << (j - 1))][j-1]);
        }
    }
    printf("%lld\n", f[n]);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    input();
    solve();

    return 0;
}
