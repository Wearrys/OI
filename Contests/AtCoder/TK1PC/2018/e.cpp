#include <bits/stdc++.h>
using namespace std;

const int N = 600;
typedef long long ll;

int n, m;
char st[N + 5][N + 5];
bool vis[N + 5][N + 5];
int cnt[2][N + 5][N + 5];

int calc(int ty, int x, int l, int r) {
    if(x < 0 || x > n + m) return 0;

    return cnt[ty][x][min(r, n+m)] - cnt[ty][x][max(l-1, 0)];
}

int main() {

    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) {
        scanf("%s", st[i] + 1);
        for(int j = 1; j <= m; ++j) if(st[i][j] == '#') {
            vis[i + j][i - j + m + 1] = true;
        }
    }

    for(int i = 1; i <= n + m; ++i) {
        for(int j = 1; j <= n + m; ++j) {
            cnt[0][i][j] = cnt[0][i][j - 1] + vis[i][j];
            cnt[1][i][j] = cnt[1][i][j - 1] + vis[j][i];
        }
    }

    ll ans = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            for(int k = 1; k <= n; ++k) {

                if(i > k && j > k && st[i-k][j] == '#' && st[i][j-k] == '#') {
                    ans += calc(0, i + j + k, i - j - k + m + 1, i + k - j + m + 1);
                }
                if(i > k && j <= m-k && st[i-k][j] == '#' && st[i][j+k] == '#') {
                    ans += calc(1, i + k - j + m + 1, i - k + j, i + j + k);
                }
                if(i <= n-k && j > k && st[i+k][j] == '#' && st[i][j-k] == '#') {
                    ans += calc(1, i - k - j + m + 1, i - k + j, i + j + k);
                }
                if(i <= n-k && j <= m-k && st[i+k][j] == '#' && st[i][j+k] == '#') {
                    ans += calc(0, i - k + j, i - j - k + m + 1, i + k - j + m + 1);
                }

                bool x = (i > k && st[i-k][j] == '#');
                bool y = (j > k && st[i][j-k] == '#');
                bool z = (i <= n-k && st[i+k][j] == '#');
                bool w = (j <= m-k && st[i][j+k] == '#');

                int c = x + y + z + w;

                if(c == 3) ans --;
                if(c == 4) ans -= 4;
            }
        }
    }
    printf("%lld\n", ans);

    return 0;
}
