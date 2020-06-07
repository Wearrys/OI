#include <bits/stdc++.h>
using namespace std;
int n, l, f[101], r[101], ans[101];
long long g[101][31][101], w[101][31][101];
int x[101][31][101], y[101][31][101];
int xx[101][31][101], yy[101][31][101];
bool cmp(const int & u, const int & v) {return f[u] < f[v];}
inline bool chkmin(long long & a, const long long& b) {
    return b < a ? a = b, 1 : 0;
}

void getans(int i, int j, int k) {
	#ifdef _noname
	printf("%d %d %d = %lld???\n", i, j, k, g[i][j][k]);
	#endif
    ans[r[i]] = j;
    if (i == 1) return;
    getans(i - 1, x[i][j][k], y[i][j][k]);
}
int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
#endif
    while (~scanf("%d%d", &n, &l)) {
        if (n == 0 && l == 0) break;
        for (int i = 1; i <= n; i++) scanf("%d", f + i);
        for (int i = 1; i <= n; i++) r[i] = i;
        sort(r + 1, r + n + 1, cmp);
        memset(g, 0x3f, sizeof g);
        memset(w, 0x3f, sizeof w);
        for (int i = 1; i <= l; i++) g[1][i][1] = (long long)i * f[r[1]], x[1][i][1] = y[1][i][1] = -1;
        for (int i = 1; i <= l; i++) w[1][i][1] = g[1][i][1], xx[1][i][1] = i, yy[1][i][1] = 1;
        w[1][0][1] = g[1][1][1], xx[1][0][1] = 1, yy[1][0][1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= l; j++) {
                for (int k = 1; k <= i - 1; k++) {
                    g[i][j][k + 1] = w[i - 1][j][k] + (long long)j * f[r[i]];
                    x[i][j][k + 1] = xx[i - 1][j][k];
                    y[i][j][k + 1] = yy[i - 1][j][k];
                }
			}
            for (int k = 1; k <= n; k++) w[i][l][k] = g[i][l][k], xx[i][l][k] = l, yy[i][l][k] = k;
            for (int j = l - 1; j >= 0; j--) {
                for (int k = 1; k <= i; k+=4) {
                    w[i][j][k] = g[i][j][k], xx[i][j][k] = j, yy[i][j][k] = k;
                }
                for (int k = 1, _end = (i + 1) / 2; k <= _end; k++) {
                    long long temp = LLONG_MAX;
                    if (chkmin(temp, w[i][j + 1][k << 1])) {
                        xx[i][j][k] = xx[i][j + 1][k << 1];
                        yy[i][j][k] = yy[i][j + 1][k << 1];
                    }
                    if (chkmin(temp, w[i][j + 1][(k << 1) - 1])) {
                        xx[i][j][k] = xx[i][j + 1][(k << 1) - 1];
                        yy[i][j][k] = yy[i][j + 1][(k << 1) - 1];
                    }
                    w[i][j][k] = temp;
                }
            }
        }
        printf("%lld\n", w[n][0][1]);
        getans(n, xx[n][0][1], yy[n][0][1]);
        for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
        puts("");
    }
    return 0;
}
