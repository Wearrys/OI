#include <bits/stdc++.h>
 
using std::pair;
using std::vector;
using std::string;

typedef long long ll;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb(a) push_back(a)
#define mp(a, b) std::make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const int oo = 0x3f3f3f3f;
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

const int N = 200;
const int mo = 1e9 + 7;

int n, k, ans;
char st[N + 5];
bool mark[N + 5];
int x[N + 5], y[N + 5], r[N + 5];

int binom[N + 5][N + 5];

void init() {
    for(int i = 0; i <= N; ++i) {
        binom[i][0] = binom[i][i] = 1;
        for(int j = 1; j < i; ++j) {
            binom[i][j] = (binom[i-1][j] + binom[i-1][j-1]) % mo;
        }
    }
}

int dp[N + 5][N + 5][N + 5];

int calc(int p, int q) {
    for(int i = 0; i <= 90; ++i) 
    for(int j = 0; j <= 90; ++j) 
    for(int t = 0; t <= 90; ++t) dp[i][j][t] = 0;

    int m = n - (p+q-1) - q;

    dp[0][0][0] = 1;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j <= p; ++j) {
            for(int l = 0; l <= m; ++l) if(dp[i][j][l]) {
                for(int t = 0; j + t <= p && l + (2*i+1) * t <= m; ++t) {
                    if(t && y[p-j-t+1] < (l-j)/2 + t*i) {
                        break;
                    }

                    (dp[i+1][j + t][l + (2*i+1) * t] += 1ll * binom[j + q + t][t] * dp[i][j][l] % mo) %= mo;
                }
            }
        }
    }

    int res = 0;
    for(int i = 0; i <= m; ++i) {
        res = (res + 1ll * binom[n + 2*p + 1][i + 3*p + 2*q] * dp[m][p][i]) % mo;
    }
    return res;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    init();
    read(n), read(k);
    scanf("%s", st + 1);

    for(int i = 1; i <= k; ++i) 
        if(st[i] == 'r') r[++ r[0]] = i;

    for(int i = 0; i <= r[0]; ++i) {
        for(int j = 0; i+j <= r[0]; ++j) {

            memset(mark, 0, sizeof mark);
            for(int t = 1; t <= i+j; ++ t) mark[r[t]] = true;

            int cur = 0, flag = 0;
            for(int t = 1; t <= i; ++ t) {
                chkmax(cur, r[t]);
                while(cur <= k && (st[cur] == 'r' || mark[cur])) ++ cur;
                if(cur > k) { flag = 1; break; }

                mark[x[t] = cur] = true;
            }
            if(flag) continue;

            for(int t = 1; t <= i; ++ t) {
                y[t] = 0;
                for(int l = x[t]; l <= k; ++ l) {
                    y[t] += !mark[l];
                }
            }
            ans = (ans + calc(i, j)) % mo;
        }
    }
    printf("%d\n", ans);

    return 0;
}
