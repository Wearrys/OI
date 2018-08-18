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

int n;
char st[200];
vector<char> a, b;

inline bool query(int x, int y, int p, int q) {
    printf("? %d %d %d %d\n", x, y, p, q);
    fflush(stdout);
    scanf("%s", st);
    return st[0] == 'Y';
}

void dfs1(int x, int y) {
    if(x + y == n + 1) return;

    if(query(x, y + 1, n, n)) 
        a.pb('R'), dfs1(x, y + 1);
    else 
        a.pb('D'), dfs1(x + 1, y);
}

void dfs2(int x, int y) {
    if(x + y == n + 1) return;

    if(query(1, 1, x - 1, y)) {
        dfs2(x - 1, y), a.pb('D'); 
    } else {
        dfs2(x, y - 1), a.pb('R');
    }
}

int main() {
#ifdef Wearry
    //freopen("in", "r", stdin);
    //freopen("out", "w", stdout);
#endif

    read(n);
    dfs1(1, 1);
    dfs2(n, n);

    printf("! ");
    for(int i = 0; i < (int) a.size(); ++i) putchar(a[i]);
    puts("");

    return 0;
}
