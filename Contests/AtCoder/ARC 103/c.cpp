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

int n, cnt = 1;
char st[N + 5];

void addedge(int u, int v) {
    printf("%d %d\n", u, v);
}

void dfs(int u, int sz) {
    for(int i = sz-1; i >= 0; --i) if(st[i] == '1') {
        if(i) { addedge(u, ++ cnt); dfs(cnt, i); }
        for(int j = 1; j < sz - i; ++j) addedge(u, ++ cnt);
        return;
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%s", st + 1);
    n = strlen(st + 1);
    if(st[1] == '0' || st[n-1] == '0' || st[n] == '1') return !puts("-1");
    for(int i = 1; i < n; ++i) if(st[i] != st[n - i]) return !puts("-1");

    dfs(1, n);

    return 0;
}
