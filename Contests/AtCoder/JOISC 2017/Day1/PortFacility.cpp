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

const int N = 2000000;

std::set<int> S, T;
typedef std::set<int>::iterator sit;

int n;
int mark[N + 5];
vector<pii> G[N + 5];

inline void addedge(int u, int v, int c) {
    G[u].pb(mp(v, c));
    G[v].pb(mp(u, c));
}

int L[N + 5], R[N + 5];
int p[N + 5], t[N + 5];

void input() {
    read(n);
    for(int i = 0; i < n; ++i) {
        int x, y;
        read(x), read(y);
        p[x] = y, t[y] = i;
    }
}

void build() {
    int x, y;
    S.insert(-oo); S.insert(oo);
    T.insert(-oo); T.insert(oo);
    for(x = 1; x <= (n << 1); ++ x) if((y = p[x]) > 0) {

        static sit it;
        it = S.upper_bound(y);

        R[y] = *it; -- it;
        L[y] = *it;

        if((*it) > x) addedge(t[y], t[*it], 1);

        static int del[N + 5], tot;

        tot = 0;
        for(it = T.upper_bound(x); (*it) < y; ++ it) {

            if(L[*it] > x) addedge(t[*it], t[L[*it]], 0), L[*it] = -oo;
            if(R[*it] < y) addedge(t[*it], t[R[*it]], 0), R[*it] = oo;

            if(L[*it] == -oo && R[*it] == oo) {
                del[++ tot] = (*it);
            }
        }
        while(tot) T.erase(del[tot--]);

        S.insert(y);
        T.insert(y);
    }
}

void dfs(int u, int c) {
    if(mark[u] >= 0) {
        if(mark[u] != c) {
            puts("0");
            exit(0);
        }
        return;
    }

    mark[u] = c;
    for(int i = 0; i < (int) G[u].size(); ++i) {
        int to = G[u][i].fst, tc = G[u][i].snd;
        dfs(to, c ^ tc);
    }
}

const int mo = 1e9 + 7;

void solve() {
    memset(mark, 0xff, sizeof mark);

    int ans = 1;
    for(int i = 0; i < n; ++i) if(!~mark[i]) {
        ans = (ans << 1) % mo;
        dfs(i, 0); 
    }
    printf("%d\n", ans);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    input();
    build();
    solve();

    return 0;
}
