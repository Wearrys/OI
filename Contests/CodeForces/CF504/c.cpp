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

const int N = 200000;

int n, k;
string s;
bool vis[N + 5];
vector<int> pos;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    read(n), read(k);
    std::cin >> s;

    for(int i = 0; i < n; ++i) {
        if(s[i] == '(') pos.pb(i);
        else if(k > 0) {
            k -= 2;
            vis[pos.back()] = vis[i] = true;
            pos.pop_back();
        }
    }
    for(int i = 0; i < n; ++i) if(vis[i]) putchar(s[i]);

    return 0;
}
