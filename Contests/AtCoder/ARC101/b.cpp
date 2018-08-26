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

const int N = 100000;

int n;
int a[N + 5], c[2*N + 5];

void clear() { memset(c, 0, sizeof c); }
void add(int x) {
    x += N + 1;
    while(x <= 2*N + 1) { 
        ++ c[x];
        x += (x & -x);
    }
}
int query(int x) {
    int res = 0;
    x += N + 1;
    while(x > 0) {
        res += c[x];
        x -= (x & -x);
    }
    return res;
}

bool chk(int x) {
    clear();
    add(0);

    int cur = 0;
    ll ans = 0;
    for(int i = 1; i <= n; ++i) {
        if(a[i] >= x) cur ++; else cur --;
        ans += query(cur)*2 - i;
        add(cur);
        //printf("%d %d\n", cur, ans);
    }
    return ans >= 0;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    for(int i = 1; i <= n; ++i) read(a[i]);

    int l = 0, r = (int) 1e9;

    while(l < r) {
        int m = (l + r + 1) >> 1;
        if(chk(m)) l = m; else r = m - 1;
    }
    printf("%d\n", l);

    return 0;
}
