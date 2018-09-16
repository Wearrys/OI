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

const int N = 100;

int n, m, ans;
int deg[N + 5];
int fa[N + 5], fb[N + 5];
bool vis[N + 5], inq[N + 5];
std::set<int> Ga[N + 5], Gb[N + 5];

bool chk() {
    for(int i = 1; i <= n; ++i) if(!vis[i]) return false;
    return true;
}

void dfs_a(int u, int f = 0) {
    fa[u] = f;
    for(auto v : Ga[u]) if(v != f) {
        dfs_a(v, u);
    }
}
void dfs_b(int u, int f = 0) {
    fb[u] = f;
    for(auto v : Gb[u]) if(v != f) {
        dfs_b(v, u);
    }
}

void solve() {

    read(n);
    ans = oo;

    for(int i = 1; i <= n; ++i) Ga[i].clear(), Gb[i].clear();
    for(int i = 1, u, v; i < n; ++i) { read(u), read(v); Ga[u].insert(v); Ga[v].insert(u); }
    for(int i = 1, u, v; i < n; ++i) { read(u), read(v); Gb[u].insert(v); Gb[v].insert(u); }

    for(int i = 1; i <= n; ++i) if(Ga[i].size() == 1) {
        int to_v = *Ga[i].begin();
        Ga[i].erase(to_v), Ga[to_v].erase(i);

        for(int j = 1; j <= n; ++j) if(j != i) {
            int cnt = n + (j != to_v);
            Ga[i].insert(j), Ga[j].insert(i);

            dfs_a(i);
            dfs_b(i);

            memset(inq, 0, sizeof inq);
            memset(vis, 0, sizeof vis);

            std::queue<int> q; q.push(i);

            inq[i] = true;
            while(!q.empty()) {
                int x = q.front(); q.pop();

                if(fa[x] == fb[x]) {
                    -- cnt; 
                    vis[x] = true;
                    inq[x] = false;
                    for(auto y : Gb[x]) if(fb[y] == x) {
                        inq[y] = true;
                        q.push(y);
                    }
                }
            }

            std::set<int> A, B;
            for(int x = 1; x <= n; ++x) {
                if(inq[x]) B.insert(x);
                if((deg[x] = Ga[x].size()) == 1) A.insert(x);
            }

            bool flag = true;
            while(flag) {
                flag = false;
                for(auto v : B) if(A.count(v)) {
                    flag = vis[v] = true;
                    for(auto t : Gb[v]) if(fb[t] == v) B.insert(t);
                    for(auto t : Ga[v]) if(--deg[t] == 1) A.insert(t);
                    B.erase(v), A.erase(v);
                }
            }

            if(chk()) {
                chkmin(ans, cnt);
            }

            Ga[i].erase(j), Ga[j].erase(i);
        }
        Ga[i].insert(to_v), Ga[to_v].insert(i);
    }
    
    printf("%d\n", ans == oo ? -1 : ans);
}

int T;
int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(T);
    while(T--) solve();

    return 0;
}
