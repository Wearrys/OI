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

const int N = 300000;

int n;
int p[N + 5];
int pre[N + 5], suf[N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    for(int i = 1; i <= n; ++i) read(p[i]);

    pre[0] = 0, suf[n+1] = oo;
    for(int i = 1; i <= n; ++i) pre[i] = std::max(pre[i-1], p[i]);
    for(int i = n; i >= 1; --i) suf[i] = std::min(suf[i+1], p[i]);

    for(int i = 1; i <= n; ++i) {
        if((p[i] ^ i) & 1) return puts("No"), 0; 
        if(i < n && (p[i] == i) == (p[i+1] == i+1) && pre[i] != i) return puts("No"), 0;
        if(i > 1 && i < n && p[i] != i && pre[i-1] > p[i] && suf[i+1] < p[i]) return puts("No"), 0;
    }
    puts("Yes");

    return 0;
}
