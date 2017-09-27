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
const int maxn = 200000 + 5;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int n;
int dp[110][2010];
pii pre[110][2010], Ed;

struct item {
    int t, d, p, id;
    bool operator < (const item& rhs) const {
        return d < rhs.d;
    }
}I[maxn];

int tot = 0;
void print_ans(int type, pii cur) {
    if(cur.fst == 0) return;
    ++ tot;
    print_ans(type, pre[cur.fst][cur.snd]);
    if(type) printf("%d ", I[cur.fst].id);
}

int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        I[i].t = read<int>();
        I[i].d = read<int>();
        I[i].p = read<int>();
        I[i].id = i;
    }

    sort(I+1, I+n+1);

    memset(dp, ~oo, sizeof dp);

    int ans = 0;
    dp[0][0] = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = i-1; j >= 0; --j) {
            for(int t = I[i].t; t < I[i].d; ++t) if(dp[j][t - I[i].t] >= 0) {
                if(chkmax(dp[i][t], dp[j][t - I[i].t] + I[i].p)) pre[i][t] = pii(j, t - I[i].t);
                if(chkmax(ans, dp[i][t])) Ed = pii(i, t);
            }
        }
    }

    printf("%d\n", ans);
    print_ans(0, Ed);
    printf("%d\n", tot);
    print_ans(1, Ed);

    return 0;
}

