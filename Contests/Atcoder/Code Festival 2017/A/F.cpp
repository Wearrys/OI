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
 
const int maxl = 35;
const int maxn = 100000 + 5;
const int oo = 0x3f3f3f3f;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int n;
int a[maxn];
int dp[2][maxl];

int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    n = read<int>();
    for(int i = 1; i <= n; ++i) { a[i] = read<int>(); }

    int cur = 0;
    memset(dp[cur], oo, sizeof dp[cur]);

    dp[cur][0] = 0;
    for(int i = 1; i <= n; ++i) {
        int bit = 0, x = 1;
        while(x < a[i]) x <<= 1, ++ bit;

        cur ^= 1;
        memset(dp[cur], oo, sizeof dp[cur]);

        for(int j = 0; j <= bit; ++j) if(dp[cur^1][j] < oo) {
            int delta = bit - j; 

            if(delta > 0 || x == a[i]) 
                chkmin(dp[cur][bit], dp[cur^1][j] + delta);
            else if(j > 0) 
                chkmin(dp[cur][bit-1], dp[cur^1][j] + delta);
        }
        for(int j = bit; j > 0; --j) chkmin(dp[cur][j-1], dp[cur][j]);
    }
    printf("%d\n", dp[cur][0]);

    return 0;
}
