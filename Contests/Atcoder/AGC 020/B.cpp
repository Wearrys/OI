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

int k;
ll a[100005];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    // freopen("out", "w", stdout);
#endif 

    read(k);
    for(int i = 1; i <= k; ++i) read(a[i]);

    ll mn = 2, mx = 2;
    for(int i = k; i >= 1; --i) {

        mx = mx / a[i];
        mn = (mn + a[i] - 1) / a[i];

        mn = mn * a[i];
        mx = mx * a[i] + a[i] - 1;

        if(mn > mx) {
            return puts("-1"), 0;
        }
    }
    printf("%lld %lld\n", mn, mx);

    return 0;
}
