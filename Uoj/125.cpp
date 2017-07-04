#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back
#define eb emplace_back
#define REP(i, a, b)  for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i=(a-1), i##end = (b); i >=i##end; --i)

template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;
const int maxn = 500 + 10;

template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int n, m;
int g[maxn][maxn];
int s1[maxn][maxn], s2[maxn][maxn];
int s[maxn], f[12][maxn][maxn], f4 = -oo, f8 = -oo;

#define f(_id) f[_id][i][j]

int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    scanf("%d%d", &n, &m);
    REP(i, 1, n+1) REP(j, 1, m+1) scanf("%d", &g[i][j]);

    int ans = -oo;
    memset(f, ~oo, sizeof f);
    memset(s1, ~oo, sizeof s1);
    memset(s2, ~oo, sizeof s2);

    REP(col, 1, m+1) {

        REP(i, 1, n+1) s[i] = s[i-1] + g[i][col];
        REP(i, 1, n+1) REP(j, i+2, n+1) chkmax(ans, f(11) = max(f(11), f(10)) + g[i][col] + g[j][col]);
        REP(i, 1, n+1) REP(j, i+2, n+1) f(10) = max(f(10), f(9)) + s[j] - s[i-1];
        REP(i, 1, n+1) REP(j, i+2, n+1) f(9) = max(f(9), f8) + g[i][col] + g[j][col];
        REP(i, 1, n+1) REP(j, i+2, n+1) chkmax(f8, f(7));
        REP(i, 1, n+1) REP(j, i+2, n+1) f(7) = f(6) + s[j] - s[i-1];
        REP(i, 1, n+1) REP(j, i+2, n+1) f(6) = max(f(6), f(5)) + g[i][col] + g[j][col];
        REP(i, 1, n+1) REP(j, i+2, n+1) f(5) = f4 + s[j] - s[i-1];
        REP(i, 1, n+1) REP(j, i+1, n+1) chkmax(f4, f(3));

        int tmp;
        REP(j, 2, n+1) {
            tmp = f[2][j][j];
            DREP(i, j, 1) {
                f(3) = max(f(3), tmp) + s[j] - s[i-1];
                chkmax(tmp, f(2));
            }
        }
        REP(i, 1, n+1) {
            tmp = s2[i-1][i-1];
            REP(j, i, n+1) {
                chkmax(tmp, s2[i][j]);
                f(2) = max(tmp, s1[i][j+1]) + s[j] - s[i-1];
            }
        }

        REP(i, 1, n+1) REP(j, i, n+1) s2[i][j] = max(s2[i-1][j], f(2));
        REP(i, 1, n+1) REP(j, i+1, n+1) f(1) = max(f(1), 0) + s[j] - s[i-1];
        REP(i, 1, n+1) DREP(j, n+1, i+1) s1[i][j] = max(s1[i][j+1], f(1));
    }
    printf("%d\n", ans);
    return 0;
}
