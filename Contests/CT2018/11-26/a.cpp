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
int sl[N + 5][N + 5], sr[N + 5][N + 5];
int fl[N + 5][N + 5][N + 5], fr[N + 5][N + 5][N + 5];
int pl[N + 5][N + 5][N + 5], pr[N + 5][N + 5][N + 5];

int p0[N + 5][N + 5], p1[N + 5][N + 5];

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

    memset(p0, -1, sizeof p0);
    memset(p1, -1, sizeof p1);

    for(int d = 2; d <= n; ++d) {
        for(int l = 1; l + d - 1 <= n; ++l) {
            int r = l + d - 1;

            pl[l][l-1][r] = oo;
            gl[l][r] = gr[l][r] = f[l][r] = oo;

            for(int m = l; m < r; ++m) { chkmin(f[l][r], gl[l][m] + gr[m+1][r]); }
            for(int m = l; m < r; ++m) {
                if(l == m) fl[l][m][r] = f[m][r];
                else {
                    if(p0[l][m] == -1) {
                        sl[l][m] = oo;
                        p0[l][m] = m - 1;
                    }
                    while(p0[l][m] >= l && c[m][p0[l][m]] < c[m][r]) 
                        chkmin(sl[l][m], fl[l][p0[l][m]][m]), -- p0[l][m];
                    fl[l][m][r] = min(pl[l][p0[l][m]][m], sl[l][m] + c[m][r]) + f[m][r];
                }
                chkmin(gl[l][r], fl[l][m][r] + c[r][m]); 
                chkmin(pl[l][m][r] = fl[l][m][r] + c[r][m], pl[l][m-1][r]);
            }

            pr[l][r+1][r] = oo;
            for(int m = r; m > l; --m) {
                if(r == m) fr[l][m][r] = f[l][m];
                else {
                    if(p1[m][r] == -1) {
                        sr[m][r] = oo;
                        p1[m][r] = m + 1;
                    }
                    while(p1[m][r] <= r && c[m][p1[m][r]] < c[m][l]) 
                        chkmin(sr[m][r], fr[m][p1[m][r]][r]), ++ p1[m][r];
                    fr[l][m][r] = min(pr[m][p1[m][r]][r], sr[m][r] + c[m][l]) + f[l][m];
                }
                chkmin(gr[l][r], fr[l][m][r] + c[l][m]);
                chkmin(pr[l][m][r] = fr[l][m][r] + c[l][m], pr[l][m+1][r]);
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
