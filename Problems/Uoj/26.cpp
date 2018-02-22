#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> pll;
typedef pair<int, int> pii;

const int oo = 0x3f3f3f3f;
const int maxn = 5000 + 10;
const int mod = 998244353;

template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

#define fst first
#define snd second
#define pb push_back
#define debug(x) cerr << #x <<":" << (x) << endl
#define REP(i, a, b) for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i = (a)-1, i##bgn = (b); i >= i##bgn; --i)

template<typename T> T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48;
	return n * f;
}

int a[maxn], n, x;
pair<LL, bool> f[1010][maxn];

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt","r", stdin);
    freopen("ans.txt","w", stdout);
#endif

    n = read<int>(); x = read<int>();
    for(int i = 1; i <= n; i++) a[i] = read<int>();
    sort(a+1, a+n+1, greater<int>());

    f[0][x].fst = f[0][x].snd = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= x; j++) {
            (f[i][j % a[i]].fst += f[i-1][j].fst) %= mod;
            f[i][j % a[i]].snd |= f[i-1][j].snd;

            if(i < n) {
                (f[i][j].fst += f[i-1][j].fst * (n-i)) %= mod;
                f[i][j].snd |= f[i-1][j].snd;
            }
        }
    }

    for(int j = x; ~j; j--) {
        if(f[n][j].snd) {
            printf("%d\n%lld\n", j, f[n][j].fst);
            return 0;
        }
    }
    return 0;
}
