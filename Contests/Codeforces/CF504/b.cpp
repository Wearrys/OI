#include <bits/stdc++.h>

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

long long n, k, lim;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(k);
    if(k % 2 == 0) lim = k / 2 + 1; else lim = (k + 1) / 2;
    printf("%lld\n", std::max(0ll, std::min(n,k-1) - lim + 1));

    return 0;
}
