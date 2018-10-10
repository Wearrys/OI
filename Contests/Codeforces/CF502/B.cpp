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

const int N = 100000;

int n;
char a[N + 5], b[N + 5];
int cnt[4];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    scanf("%s%s", a, b);
    for(int i = 0; i < n; ++i) {
        int x = a[i] - '0', y = b[i] - '0';
        ++ cnt[x | y << 1];
    }
    printf("%lld\n", 1ll * cnt[0] * (cnt[3] + cnt[1]) + 1ll * cnt[2] * cnt[1]);

    return 0;
}
