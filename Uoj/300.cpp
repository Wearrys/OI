#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back

template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int mod = 1e9 + 7;
const int maxn = 2.5e5 + 10;
const int oo = 0x3f3f3f3f;

template<typename T> T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int n, a, dp[maxn];
const int BLK = 1 << 9;

int main() {
#ifndef ONLINE_JUDGE
    freopen("ex_gift7.in", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif
    scanf("%d", &n);

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        a = read<int>();

        int tmp = 0;
        int t = (a & (BLK-1)), d = a ^ t;

        for(int j = t; j < BLK; j = (j+1) | t) 
            (tmp += dp[j + d]) >= mod ? tmp -= mod : 1;

        (ans += tmp++) >= mod ? ans -= mod : 1;
        for(int j = a; j >= BLK; j = (j-BLK) & a) 
            (dp[j] += tmp) >= mod ? dp[j] -= mod : 1;
        (dp[t] += tmp) >= mod ? dp[t] -= mod : 1;
    }
    printf("%d\n", ans);

    return 0;
}
