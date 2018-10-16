#include <bits/stdc++.h>
using namespace std;

const int N = 1500;
const int oo = 0x3f3f3f3f;

int n;
int a[N + 5][N + 5];
int f[N + 5][N + 5];
char st[N + 5][N + 5];
int L[N + 5][N + 5], R[N + 5][N + 5];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%s", st[i] + 1);
        for(int j = 1; j <= n; ++j) {
            a[i][j] = (st[i][j] == '#') ? 0 : st[i][j] - '0';
        }
    }

    long long ans = 0;
    for(int j = n; j >= 1; --j) if(a[n][j] > 0) {
        L[n][j] = j; 

        if(a[n][j + 1] > 0) {
            f[n][j] = f[n][j + 1];
            R[n][j] = R[n][j + 1];
        } else {
            R[n][j] = j;
        }

        ans += a[n][j] * f[n][j];
        f[n][j] += a[n][j];
    }

    for(int i = n - 1; i >= 1; --i) {
        for(int j = n; j >= 1; --j) if(a[i][j] > 0) {
            bool r = (a[i][j + 1] > 0), d = (a[i + 1][j] > 0);

            if(!r && !d) {
                L[i][j] = R[i][j] = j;
                for(int k = i + 1; k <= n; ++k) L[k][j] = oo, R[k][j] = -oo;
            } else if(r && !d) {
                L[i][j] = j;
                R[i][j] = R[i][j + 1];
                f[i][j] = f[i][j + 1];
                for(int k = i + 1; k <= n; ++k) L[k][j] = L[k][j + 1], R[k][j] = R[k][j + 1];
            } else if(!r && d) {
                f[i][j] = f[i + 1][j];
                L[i][j] = R[i][j] = j;
            } else {
                L[i][j] = j; R[i][j] = R[i][j + 1];
                f[i][j] = f[i + 1][j] + f[i][j + 1];

                int lim = 0;
                for(int k = i + 1; k <= n; ++k) {
                    if(R[k][j] >= L[k][j + 1] && L[k][j + 1] > lim) {
                        f[i][j] -= f[k][L[k][j + 1]];
                    }
                    lim = R[k][j];
                    L[k][j] = min(L[k][j], L[k][j + 1]);
                    R[k][j] = max(R[k][j], R[k][j + 1]);
                }
            }
            
            ans += a[i][j] * f[i][j];
            f[i][j] += a[i][j];
        }
    }
    printf("%lld\n", ans);

    return 0;
}
