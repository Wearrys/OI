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

int Q;
int a, b;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(Q);
    while(Q--) {
        read(a), read(b);
        if(a > b) std::swap(a, b);

        if(a == 1 && b == 1) {
            puts("0");
            continue;
        }

        ll ans = 0;
        ll s = (ll) a * b - 1, r = std::max(0ll, (ll)sqrt(s) - 5);

        while((r + 1) * (r + 1) <= s) ++ r;

        ll t = s / r;
        ans = 2 * r - (t == r);

        printf("%lld\n", ans - (a <= r));
    }

    return 0;
}
