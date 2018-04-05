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
inline int query(int pos) {
    printf("%d\n", pos);
    fflush(stdout);

    static char op[25];
    scanf("%s", op);

    if(op[0] == 'V') exit(0);
    if(op[0] == 'F') return 0;
    if(op[0] == 'M') return 1;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);

    int t0 = query(0);
    int l = 0, r = n - 1;

    while(l <= r) {
        int m = (l + r) >> 1;
        if(((m & 1) ^ query(m)) == t0) l = m + 1; else r = m - 1; 
    }

    return 0;
}
