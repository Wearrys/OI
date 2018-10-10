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

int n, m;
string s, t;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(m);
    std::cin >> s >> t;

    int l = -1, r = m;
    for(int i = 0; i < n && s[i] != '*'; ++i) {
        if(i >= m || s[i] != t[i]) return puts("NO"), 0;
        l = i;
    }
    for(int i = n-1; i >= 0 && s[i] != '*'; --i) {
        -- r;
        if(r < 0 || s[i] != t[r]) return puts("NO"), 0;
    }
    puts((l < r || (l == n-1 && r == 0 && l == m-1)) ? "YES" : "NO");

    return 0;
}
