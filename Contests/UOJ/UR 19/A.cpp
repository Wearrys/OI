#include <bits/stdc++.h>

typedef long long ll;

using std::pair;
using std::vector;
using std::string;

#define fst first
#define snd second
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)

template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;

template<typename T> T read(T& x) {
    T f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = 200000;
const int S = 1 << 18;

int a[N + 5];
ll dp[S + 5];
bool chk[S + 5], mark[N + 5];
int n, all, lim;

void get_lim() {
    int u, mn = oo;
    for(int i = 0; i < n; ++i) if(chkmin(mn, a[i])) u = i;

    mark[u] = true;
    lim += mn;

    while(true) {
        for(int i = 0; i < n; ++i) if(!mark[i]) { a[i] &= mn; }

        int temp = mn; 
        mn = oo, u = -1;
        for(int i = 0; i < n; ++i) if(!mark[i] && chkmin(mn, a[i])) u = i;

        if(u == -1 || mn == temp) break;

        lim += mn;
        mark[u] = true;
    }
    for(int i = 0; i < n; ++i) if(!mark[i]) lim += a[i];
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), all = S - 1;
    for(int i = 0; i < n; ++i) all &= read(a[i]);
    for(int i = 0; i < n; ++i) a[i] ^= all, chk[a[i]] = true;

    get_lim();

    for(int i = 0; i < S; ++i) if(chk[i])
        for(int j = 0; j < 18; ++j) if(!(i >> j & 1)) chk[i | (1 << j)] = true;

    memset(dp, oo, sizeof dp);
    dp[S - 1] = 0;

    for(int i = S - 1; i >= 0; --i) if(dp[i] <= lim) {
        for(int j = i; ; j = (j-1) & i) {
            if(chk[(S-1) ^ j]) 
                chkmin(dp[i ^ j], dp[i] + (i ^ j));
            if(!j) break;
        }
    }
    printf("%lld\n", dp[0] + 1ll * n * all);

    return 0;
}
