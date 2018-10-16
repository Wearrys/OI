#include <bits/stdc++.h>
using namespace std;

const int N = 600;
const int mo = 1e9 + 7;

int n, m;
int dp[N + 5][N + 5];
int f[N + 5], lnk[N + 5];
int a[N + 5], b[N + 5], s[N + 5];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d", a + i, b + i);
        ++ s[a[i]], ++ s[b[i]];
        lnk[lnk[b[i]] = a[i]] = b[i];
    }

    n <<= 1;
    for(int i = 1; i <= n; ++i) s[i] += s[i-1];
    
    f[0] = f[2] = 1;
    for(int i = 4; i <= N; i += 2) f[i] = 1ll * (i - 1) * f[i - 2] % mo;

    int ans = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = i + 1; j <= n; j += 2) {
            bool flag = true;
            for(int k = i; k <= j; ++k) if(lnk[k] && (lnk[k] < i || lnk[k] > j)) {
                flag = false;
                break;
            }
            if(!flag) continue;

            dp[i][j] = f[j - i + 1 - (s[j] - s[i-1])];
            for(int k = i; k < j; ++k) dp[i][j] = (dp[i][j] - 1ll * dp[i][k] * f[j - k - (s[j] - s[k])]) % mo;

            ans = (ans + 1ll * dp[i][j] * f[n - (j - i + 1) - (2 * m - (s[j] - s[i-1]))]) % mo;
        }
    }
    printf("%d\n", ans);

    return 0;
}
