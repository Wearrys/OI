#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

const int oo = 0x3f3f3f3f;
const int maxn = 1000000 + 10;

template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

#define fst first
#define snd second
#define debug(x) cerr << #x << ":" << (x) << endl
#define REP(i, a, b) for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i = (a)-1, i##bgn = (b); i >= i##bgn; --i)

template<typename T> T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48;
	return n * f;
}

long long n, a, X;
long long s[maxn], sum, ans = 1LL << 50;

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif
    
    scanf("%lld", &n);
    for(int i = 0; i < n; i++) 
        ++ s[a = read<int>()], chkmax(X, a), sum += a;
    for(int i = maxn-2; i >= 1; i--) s[i] += s[i+1];

    for(int x = 1; x <= X; x++) {
        long long res = 0;
        for(int p = x; p <= X; p += x)
            res += s[p];
        chkmin(ans, res * (1-x) + sum);
    }
    printf("%lld\n", ans);
    return 0;
}
