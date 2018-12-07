#include <bits/stdc++.h>
 
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
 
const int oo = 0x3f3f3f3f;
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

const int N = 6;
const int C = 50;

int n, c;
int l[N + 5];
ll dp[N * (C + 5)][(1 << N) + 5], ans, tot;

ll calc() {
    memset(dp, 0, sizeof dp);

    dp[0][0] = 1;
    for(int i = 0; i < (n+1) * c; ++i) {
        int t = i % (n+1) - 1;
        if(t < 0) continue;

        for(int j = 0; j < i; ++j) {
            for(int k = 0; k < (1 << n); ++k) if(!(k >> t & 1)) {

                if(i - (n+1) * l[t] <= j) 
                    dp[i][k | (1 << t)] += dp[j][k];
                else 
                    dp[j][k | (1 << t)] += dp[j][k];
            }
        }
    }

    ll res = 0;
    for(int i = (c-l[n]) * (n+1); i < (n+1) * c; ++i) {
        ans += dp[i][(1 << n) - 1];
    }
    return res;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    // freopen("out", "w", stdout);
#endif 

    read(n), read(c);
    for(int i = 0; i < n; ++i) { read(l[i]); }
    std::sort(l, l + n);

    n--;
    do {
        ++ tot;
        ans += calc();
    } while(std::next_permutation(l, l + n));

    for(int i = 0; i < n; ++i) tot *= c;
    printf("%.15lf\n", (double) ans / tot);

    return 0;
}
