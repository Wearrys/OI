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

const int N = 1 << 18;

int n;
pii s[N + 5];

void upd(pii& a, pii b) {
    if(b.fst >= a.fst) {
        chkmax(a.snd, a.fst);
        a.fst = b.fst;
        chkmax(a.snd, b.snd);
    } else {
        chkmax(a.snd, b.fst);
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    for(int i = 0; i < (1 << n); ++i) read(s[i].fst);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < (1 << n); ++j) if(j >> i & 1) {
            upd(s[j], s[j ^ (1 << i)]);
        }
    }

    int ans = 0;
    for(int i = 1; i < (1 << n); ++i) {
        chkmax(ans, s[i].fst + s[i].snd);
        printf("%d\n", ans);
    }

    return 0;
}
