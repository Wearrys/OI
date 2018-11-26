#include <bits/stdc++.h>
using namespace std;

const int N = 100;

void chkmin(int&a, int b) {
    (a > b) ? a = b : 0;
}

int n;
long long a[N + 5];
int f[N + 5][N + 5][N + 5][N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%lld", a + i);

    memset(f, 0x3f, sizeof f);

    for(int i = 1; i <= n; ++i) {
        vector<long long> vec;
        for(int j = 1; j <= n; ++j) vec.push_back(abs(a[i] - a[j]));

        sort(vec.begin(), vec.end());
        for(int j = 1; j <= i; ++j) {
            for(int k = i; k <= n; ++k) {
                f[i][i][j][k] = 
                    upper_bound(vec.begin(), vec.end(), max(abs(a[i] - a[j]), abs(a[i] - a[k]))) - vec.begin();
            }
        }
    }

    for(int l = 2; l <= n; ++l) {
        for(int i = 1; i + l - 1 <= n; ++i) {
            int j = i + l - 1;
            for(int k = i; k < j; ++k) {
                for(int c = 1; c <= i; ++c) {
                    for(int d = j; d <= n; ++d) {
                        chkmin(f[i][j][c][d], f[i][k][c][d] + f[k+1][j][i][j]);
                        chkmin(f[i][j][c][d], f[i][k][i][d] + f[k+1][j][c][j]);
                        chkmin(f[i][j][c][d], f[i][k][c][j] + f[k+1][j][i][d]);
                        chkmin(f[i][j][c][d], f[i][k][i][j] + f[k+1][j][c][d]);
                    }
                }
            }
        }
    }
    printf("%d\n", f[1][n][1][n]);

    return 0;
}
