#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back

template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int maxn = 400 + 5;
const int oo = 0x3f3f3f3f;
const int mod = 1e9 + 7;

template<typename T> T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48;
	return n * f;
}

int n, q;
LL S[maxn][maxn];
LL a[maxn], d[maxn], C[maxn];
LL dp[2][maxn][maxn], f[maxn][maxn];


template<typename T> inline T MOD(T& x) { 
    return x >= mod ? x -= mod : x;
}

void calc(int l, int r, int p) {
    memset(dp, 0, sizeof dp);

    dp[0][l][r] = 1;

    int cur = 1;
    for(int i = 1; i <= q; i++) {

        for(int j = l; j <= r; j++) {
            int tmp = 0;
            for(int k = r; k >= j; k--) {
                dp[cur][j][k] = tmp; 
                tmp = (tmp + dp[cur^1][j][k] * (n-k)) % mod;
            }
        }
        for(int k = l; k <= r; k++) {
            int tmp = 0;
            for(int j = l; j <= k; j++) {
                MOD(dp[cur][j][k] += tmp);
                tmp = (tmp + dp[cur^1][j][k] * (j-1)) % mod;
            }
        }

        for(int j = l; j <= r; j++) 
            for(int k = j; k <= r; k++)
                dp[cur][j][k] = (dp[cur][j][k] + dp[cur^1][j][k]*f[j][k]) % mod;

        cur ^= 1;
    }

    int pos = lower_bound(d+1, d+n+1, a[p]) - d;

    for(int i = l; i <= r; i++) {
        int tmp = 0;
        for(int j = r; j >= i; j--) {
            MOD(tmp += dp[cur^1][i][j]);
            MOD(S[j][pos] += tmp);
        }
    }
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    n = read<int>();
    q = read<int>();
    for(int i = 1; i <= n; i++) {
        d[i] = a[i] = read<int>();
        C[i] = (i*(i+1) >> 1);
    }

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            f[i][j] = C[i-1] + C[n-j] + C[j-i+1];
    
    sort(d + 1, d + n + 1);

    for(int i = 1; i <= n; i++) {
        int l = i, r = i;
        while(l - 1 >= 1 && a[l-1] <= a[i]) -- l;
        while(r + 1 <= n && a[r+1] <= a[i]) ++ r;

        calc(l, r, i);
    }

    for(int i = 1; i <= n; i++) {
        int ans = 0, tmp = 0;
        for(int j = 1; j <= n; j++)  {
            if(S[i][j]) {
                ans = (ans + (S[i][j]-tmp+mod)*d[j] % mod) % mod;
                tmp = S[i][j];
            }
        }
        printf("%d%c", ans, " \n"[i==n]);
    }
    return 0;
}
