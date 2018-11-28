#include <bits/stdc++.h>
using namespace std;

const int N = 300;
const int oo = 0x3f3f3f3f;

template <typename T> inline bool chkmin(T& a, T b) { return (a > b) ? a = b, 1 : 0; }

int n;
long long a[N + 5];
int c[N + 5][N + 5];
int g[N +  5][N + 5], f[N + 5][N + 5];
int gl[N + 5][N + 5], gr[N + 5][N + 5];
int fl[N + 5][N + 5][N + 5], fr[N + 5][N + 5][N + 5];
int pl[N + 5][N + 5][N + 5], pr[N + 5][N + 5][N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%lld", a + i);
    for(int i = 1; i <= n; ++i) {
        vector<long long> vec;
        for(int j = 1; j <= n; ++j) vec.push_back(abs(a[i] - a[j]));
        sort(vec.begin(), vec.end());
        for(int j = 1; j <= n; ++j) {
            c[i][j] = upper_bound(vec.begin(), vec.end(), abs(a[i] - a[j])) - vec.begin();
        }
    }

    for(int d = 2; d <= n; ++d) {
        for(int l = 1; l + d - 1 <= n; ++l) {
            int r = l + d - 1;
            gl[l][r] = gr[l][r] = f[l][r] = oo;
            for(int m = l; m < r; ++m) { chkmin(f[l][r], gl[l][m] + gr[m+1][r]); }
            for(int m = l; m < r; ++m) {
                fl[l][m][r] = (l == m) ? f[m][r] : oo;
                for(int p = l; p < m; ++p) 
                    chkmin(fl[l][m][r], fl[l][p][m] + f[m][r] + max(c[m][p], c[m][r]));
                chkmin(gl[l][r], fl[l][m][r] + c[r][m]); 
                pl[l][m][r] = fl[l][m][r] + c[m][r];
                if(m > l) chkmin(pl[l][m][r], pl[l][m-1][r]);
            }
            for(int m = r; m > l; --m) {
                fr[l][m][r] = (r == m) ? f[l][m] : oo;
                for(int p = r; p > m; --p) 
                    chkmin(fr[l][m][r], fr[m][p][r] + f[l][m] + max(c[m][p], c[m][l]));
                chkmin(gr[l][r], fr[l][m][r] + c[l][m]);
            }
        }
    }

    for(int l = 1; l <= n; ++l) {
        for(int r = l + 1; r <= n; ++r) {
            g[l][r] = oo;
            if(l == 1) g[l][r] = f[l][r] + c[l][r];
            else {
                for(int m = 1; m < l; ++m) {
                    chkmin(g[l][r], g[m][l] + max(c[l][m], c[l][r]) + f[l][r]);
                }
            }
        }
    }

    int ans = oo;
    for(int i = 1; i < n; ++i) chkmin(ans, g[i][n] + c[n][i]);
    printf("%d\n", ans);

    return 0;
}
