#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back
#define getchar getchar_unlocked

template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;
const int maxn = 1e5 + 10;
const int mod = 1e9 + 7;

template<typename T> inline T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48;
	return n * f;
}

LL n, n1, m, m1, a, b, c, d;

LL fpm(LL base, LL exp) {
    LL ans = 1;
    for(; exp > 0; exp >>= 1) {
        if(exp & 1) 
            ans = ans * base % mod;
        base = base * base % mod;
    }return ans;
}
void readmod(LL &a1, LL &a2) {
    a1 = a2 = 0;
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar());
    for( ; isdigit(ch); ch = getchar()) 
        a1 = (a1 * 10 + ch - 48) % mod,
        a2 = (a2 * 10 + ch - 48) % (mod-1);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    readmod(n, n1); readmod(m, m1);
    
    a = read<LL>(); b = read<LL>();
    c = read<LL>(); d = read<LL>();

    LL S = fpm(a, (m1-1+mod-1) % (mod-1));
    LL D = ((a == 1 ? (m-1+mod)%mod : ((fpm(a, (m1-1+mod-1) % (mod-1))-1) * fpm(a-1, mod-2) % mod))) * b % mod;

    LL tmp1 = S + D;
    tmp1 = (tmp1 >= mod ? tmp1 - mod : tmp1);

    c = S*c % mod;
    d = (S*d + D) % mod;

    LL tmp2 = 
        tmp1 * fpm(c, (n1-1+mod-1) % (mod-1)) % mod 
            + 
        (c == 1 ? (n-1+mod)%mod : ((fpm(c, (n1-1+mod-1) % (mod-1))-1) * fpm(c-1, mod-2) % mod)) * d % mod;

    printf("%lld\n", tmp2 >= mod ? tmp2-mod : tmp2);
    return 0;
}
