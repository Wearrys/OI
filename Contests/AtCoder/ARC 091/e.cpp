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

int n, a, b;
int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(a), read(b);

    if(a + b - 1 > n || 1ll * a * b < n) return !puts("-1");

    for(int i = n - a + 1; i <= n; ++i) { printf("%d ", i); }

    if(b > 1) {
        int all = n - a, t = all / (b - 1);
        int res = all % (b - 1);

        while (all >= 1) {
            int flag = 0;
            if(res > 0 && res --) flag = 1;
            for(int j = std::max(1, all - t -flag + 1); j <= all; ++j) printf("%d ", j);
            all -= t+flag;
        }
    }

    return 0;
}
