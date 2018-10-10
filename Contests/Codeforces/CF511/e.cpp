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

const int N = 1 << 21;

#define bitcnt __builtin_popcount
typedef unsigned long long ull;

int n;
char st[N + 5];
ull a[N + 5], b[N + 5];

void fmt(ull *f) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < (1 << n); ++j) if(j >> i & 1) {
            f[j] += f[j ^ (1 << i)];
        }
    }
}

void ifmt(ull *f) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < (1 << n); ++j) if(j >> i & 1) {
            f[j] -= f[j ^ (1 << i)];
        }
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    scanf("%s", st); for(int i = 0; i < (1 << n); ++i) a[i] = ull(st[i] - '0') << (bitcnt(i) << 1); 
    scanf("%s", st); for(int i = 0; i < (1 << n); ++i) b[i] = ull(st[i] - '0') << (bitcnt(i) << 1);

    fmt(a);
    fmt(b);
    for(int i = 0; i < (1 << n); ++i) a[i] *= b[i];

    ifmt(a);
    for(int i = 0; i < (1 << n); ++i) putchar('0' + ((a[i] >> (bitcnt(i) << 1)) & 3));

    return 0;
}
