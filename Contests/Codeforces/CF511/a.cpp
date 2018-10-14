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

const int N = 15000000;

bool notprime[N + 5];
int prime[N + 5], mn[N + 5], cnt[N + 5], pcnt;

void sieve() {
    for(int i = 2; i <= N; ++i) {
        if(!notprime[i]) {
            mn[i] = i;
            prime[pcnt ++] = i;
        }
        for(int j = 0; j < pcnt && 1ll * i * prime[j] <= N; ++j) {
            notprime[i * prime[j]] = true;
            mn[i * prime[j]] = prime[j];
            if(i % prime[j] == 0) break;
        }
    }
}

int n, gcd;
int a[N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    sieve();
    read(n);
    for(int i = 1; i <= n; ++i) {
        read(a[i]);
        if(i == 1) gcd = a[1]; else gcd = std::__gcd(gcd, a[i]);

        int k = a[i];
        while(k > 1) {
            int x = mn[k], t = 1;
            while(k % x == 0) k /= x, t *= x, ++ cnt[t]; 
        }
    }

    int ans = oo;
    for(int i = 2; i <= N; ++i) if(gcd % i != 0) {
        chkmin(ans, n - cnt[i]);
    }
    printf("%d\n", ans >= n ? -1 : ans);

    return 0;
}
