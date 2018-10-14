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

int n, m;
int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    read(n), read(m);
    if(n > m) std::swap(n, m);

    if(n == 1) {
        int x = m % 6;
        if(x % 6 >= 4)
            printf("%d\n", m - x + (x - 3) * 2);
        else 
            printf("%d\n", m - x);
    }
    if(n == 2) {
        if(m <= 2) puts("0");
        if(m == 3) puts("4");
        if(m > 3) {
            if(m == 7) 
                printf("%d\n", 12);
            else 
                printf("%lld\n", 1ll * n * m);
        }
    }
    if(n > 2) {
        ll ans = 1ll * n * m;
        printf("%lld\n", (ans & 1) ? ans - 1 : ans);
    }

    return 0;
}
