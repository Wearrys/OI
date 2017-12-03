#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp> //__gnu_pbds::priority_queue
 
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
 
const int N = 3000;
const int oo = 0x3f3f3f3f;
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

int n, m;
int d[4][4], A, B;
char a[N + 5], b[N + 5];
int dp[N + 5][N + 5][2][2];

int mp[256];
int main() {

    //freopen("A.in", "r", stdin);

    scanf("%s%s", a + 1, b + 1);
    n = strlen(a + 1), m = strlen(b + 1);

    for(int i = 0; i < 4; ++i) 
        for(int j = 0; j < 4; ++j) read(d[i][j]);
    read(A), read(B);

    mp['A'] = 0;
    mp['T'] = 1;
    mp['G'] = 2;
    mp['C'] = 3;

    memset(dp, ~oo, sizeof dp);

    dp[1][1][0][0] = 0;
    for(int i = 1; i <= n+1; ++i) {
        for(int j = 1; j <= m+1; ++j) {
            int x = mp[a[i]], y = mp[b[j]];

            for(int p = 0; p < 2; ++p) 
            for(int q = 0; q < 2; ++q) {
                chkmax(dp[i + 1][j + 1][0][0], dp[i][j][p][q] + d[x][y]);

                if(i <= n) {
                    if(!q) chkmax(dp[i + 1][j][0][1], dp[i][j][p][q] - A);
                    else   chkmax(dp[i + 1][j][0][1], dp[i][j][p][q] - B);
                }
                if(j <= m) {
                    if(!p) chkmax(dp[i][j + 1][1][0], dp[i][j][p][q] - A);
                    else   chkmax(dp[i][j + 1][1][0], dp[i][j][p][q] - B);
                }
            }
        }
    }

    int ans = std::max( std::max(dp[n + 1][m + 1][0][0], dp[n + 1][m + 1][0][1]),
                        std::max(dp[n + 1][m + 1][1][0], dp[n + 1][m + 1][1][1]) );
    printf("%d\n", ans);

    return 0;
}
