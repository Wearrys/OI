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
const int mod = 1e9 + 7;

const int maxn = 1000 + 10;
const int maxp = (1 << 15) + 5;

template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

#define lowbit(a) (a) & -(a)
#define bitcnt __builtin_popcount

int n, m, Maxp;
LL dp[maxp], h[maxp], p[maxp];
LL in[maxp], out[maxp], c[maxp], pw[maxn];

int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif
    
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; ++i) {
        static int u, v;
        scanf("%d%d", &u, &v);
        u = 1 << (u-1); v = 1 << (v-1);
        in[v] |= u; out[u] |= v;
    }

    pw[0] = 1;
    for(int i = 1; i <= n*n; ++i) 
        pw[i] = (pw[i-1] << 1) % mod;

    for(int s = 1; s < (1 << n); ++ s) {
        int u = lowbit(s), other = s ^ u;
        for(int t = other; t; t = (t-1) & other) 
            p[s] = (p[s] - dp[s ^ t] * p[t]) % mod;

        h[s] = h[other] + bitcnt(in[u] & s) + bitcnt(out[u] & s);

        dp[s] = pw[h[s]];
        for(int t = s; t; t = (t-1) & s) {
            if(t == s) c[t] = 0;
            else {
                int v = lowbit(s ^ t);
                c[t] = c[t ^ v] + bitcnt(t & in[v]) - bitcnt((s ^ t ^ v) & out[v]);
            }
            dp[s] = (dp[s] - p[t] * pw[h[s ^ t] + c[t]] % mod) % mod;
        }
        p[s] = (p[s] + dp[s]) % mod;
    }
    printf("%lld\n", (dp[(1<<n) - 1] + mod) % mod);

    return 0;
}
