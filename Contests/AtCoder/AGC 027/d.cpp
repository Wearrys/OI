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

string procStatus() {
    std::ifstream t("/proc/self/status");
    return string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}

template <typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

int n;
ll a[505][505];
std::set<ll> s;

inline bool chk(int x) {
    for(int i = 2; (ll)i*i <= x; ++i) {
        if(x % i == 0) return false;
    }
    return true;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    vector<int> v;
    for(int i = 2; ; ++i) {
        if(chk(i)) { v.pb(i); }
        if(v.size() == 1002) break;
    }

    read(n);
    if(n == 2) {
        puts("4 7");
        puts("23 10");
        return 0;
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if((i+j)%2==0) {
                a[i][j] = 1ll * v[(i+j)/2] * v[(i-j)/2+750];
                s.insert(a[i][j]);
            }
        }
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if((i+j)&1) {
                ll lcm = 1;
                if(i>1) lcm = a[i-1][j] / std::__gcd(lcm, a[i-1][j]) * lcm;
                if(i<n) lcm = a[i+1][j] / std::__gcd(lcm, a[i+1][j]) * lcm;
                if(j>1) lcm = a[i][j-1] / std::__gcd(lcm, a[i][j-1]) * lcm;
                if(j<n) lcm = a[i][j+1] / std::__gcd(lcm, a[i][j+1]) * lcm;

                a[i][j] = lcm + 1;
                s.insert(a[i][j]);
            }
        }
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            printf("%lld ", a[i][j]);
        }
        puts("");
    }

    return 0;
}
