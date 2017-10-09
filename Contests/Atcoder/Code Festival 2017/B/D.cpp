#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb push_back
#define REP(i, a, b)  for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i=(a-1), i##end = (b); i >=i##end; --i)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const int oo = 0x3f3f3f3f;
const int maxn = 500000 + 5;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

char st[maxn];
int a[maxn], l[maxn], r[maxn];

vector<pii> G[maxn];

int main() {
#ifdef Wearry
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    int n = read<int>();
    scanf("%s", st + 1);

    for(int i = 1; i <= n; ++i) if(st[i] == '1') l[i] = (i > 1 && st[i-1] == '1') ? l[i-1] : i;
    for(int i = n; i >= 1; --i) if(st[i] == '1') r[i] = (i < n && st[i+1] == '1') ? r[i+1] : i;

    for(int i = 2; i < n; ++i) if(st[i] == '0') {
        if(st[i-1] == '1' && st[i+1] == '1') {
            G[l[i-1]].pb(pii(i+1, i - l[i-1]));
            G[i-1].pb(pii(r[i+1], r[i+1] - i));
            G[l[i-1] + 1].pb(pii(i+1, i - l[i-1] - 1));
            G[i-1].pb(pii(r[i+1] - 1, r[i+1] - i - 1));
        }
    }

    static int dp[maxn], ans = 0;

    dp[0] = 0;
    for(int i = 1; i <= n + 1; ++i) {
        chkmax(dp[i], dp[i-1]);
        for(int j = 0; j < int(G[i].size()); ++j) {
            chkmax(dp[G[i][j].fst+1], dp[i] + G[i][j].snd);
        }
        chkmax(ans, dp[i]);
    }

    printf("%d\n", ans);
    return 0;
}
