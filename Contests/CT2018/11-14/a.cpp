#include <bits/stdc++.h>
using namespace std;

const int mo = 998244353;
const int N = 6, M = 100;

typedef long long ll;

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = (ll) res * x % mo;
        x = (ll) x * x % mo;
    }
    return res;
}

int n, m;
char st[N + 5][M + 5];
int dp[M + 5][1 << N][N * M * 2 + 5];

int get_s(int c) {
    int res = 0;
    for(int i = 0; i < n; ++i) {
        if(st[i][c] == '*') res |= 1 << i;
    }
    return res;
}

#define bitcnt __builtin_popcount

inline int sgn(int s) {
    return (bitcnt(s) & 1) ? -1 : 1;
}

inline int e(int x, int y) {
    if(x >> y & 1)
        x ^= (1 << y);
    return x;
}

void add(int &a, int b) {
    a += b;
    a %= mo;
}

int tot;
int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) {
        scanf("%s", st[i]);
        for(int j = 0; j < m; ++j) tot += (st[i][j] == '*');
    }

    static int cnt[1 << N];
    for(int i = 0; i < (1 << n); ++i) {
        for(int j = 0; j < (n - 1); ++j) if((i >> j & 1) || (i >> (j+1) & 1)) {
            ++ cnt[i];
        }
    }

    int c = 2*n*m-n-m;
    for(int i = 0; i < m; ++i) {
        int S = get_s(i);
        if(i == 0) {
            for(int j = S; ; j = (j - 1) & S) {
                dp[i][j][cnt[j]] = sgn(j) * (-1);
                if(!j) break;
            }
        } else {
            for(int k = 0; k < (1 << n); ++k) {
                for(int l = 0; l <= 2 * i * n; ++l) if(dp[i-1][k][l]) {
                    dp[i][k][l] = dp[i-1][k][l];
                }
            }

            for(int j = 0; j < n; ++j) {
                static int tmp[1 << N][N*M*2 + 5];

                memset(tmp, 0, sizeof tmp);
                for(int k = (1 << n) - 1; k >= 0; --k) {
                    for(int l = 2*(i+1)*n; l >= 0; --l) if(dp[i][k][l]) {
                        int d = (j > 0 && (k >> (j-1) & 1));
                        add(tmp[e(k, j)][l + d + (k >> j & 1)], dp[i][k][l]);

                        if(st[j][i] == '*') 
                            add(tmp[k | (1 << j)][l + (j > 0) + 1], -dp[i][k][l]);
                    }
                }
                memcpy(dp[i], tmp, sizeof dp[i]);
            }
        }
    }

    int ans = 0;
    for(int i = 0; i < (1 << n); ++i)
        for(int j = 1; j <= c; ++j) if(dp[m-1][i][j]) {
            ans = (ans + (ll) dp[m-1][i][j] * c % mo * fpm(j, mo - 2)) % mo;
        }

    ans = (ans + mo) % mo;
    printf("%d\n", ans);
    return 0;
}
