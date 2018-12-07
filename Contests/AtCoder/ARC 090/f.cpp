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

const int mo = 1e9 + 7;
const int N = 10000000;

int S;
ll ans;
int f[N + 5];

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = 1ll * res * x % mo;
        x = 1ll * x * x % mo;
    }
    return res;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif 

    int l = 1, r = 0, cur = 0;
    ll cnt = 0, sum = 0;

    read(S);
    for(int i = 1; i < N; ++i) sum += (f[i] = f[i/10] + 1);
    for(int i = 1; i < N; ++i) {

        while(cur < S && r < N) cur += f[r ++];

        if(cur == S) ++ ans;
        cur -= f[l ++];
        if(sum - cnt < S && (S - (sum - cnt)) % 8 == 0) ++ ans;

        cnt += f[i];
    }

    for(int i = 1; i <= S/8; ++i) {
        if(S % i == 0) {
            ans = (ans + 9ll * fpm(10, (S/i)-1) % mo - i + 1) % mo;
        } else 
            ++ ans;
    }
    printf("%lld\n", (ans + mo) % mo);

    return 0;
}
