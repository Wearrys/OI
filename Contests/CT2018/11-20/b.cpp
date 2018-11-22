#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define getchar getchar_unlocked
#define putchar putchar_unlocked

inline void write(int x) {
    int top = 0;
    static char st[15];

    do {
        st[top ++] = x % 10 + '0';
    } while(x /= 10);

    while(top--) {
        putchar(st[top]);
    }
}

template <typename T> T read(T& x) {
    T f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

namespace G {
    const int N = 30;

    int d[N], dcnt;

    template <typename T> 
    void dfs(int dep, T g, int x, int y, int z, int n) {
        if(dep > dcnt) { g[x-1][y-1] = z-1; return; }

        int t = n / d[dep];
        for(int i = 0; i < n; i += t) 
            for(int j = 0; j < n; j += t) 
                dfs(dep + 1, g, x + i, y + j, z + (i + j) % n, t);
    }

    template <typename T1, typename T2>
    int init(int t, T1 a, T2 g) {
        int n = 1;
        dcnt = t;
        for(int i = 1; i <= t; ++i) n *= d[i] = a[i];
        dfs(1, g, 1, 1, 1, n);
        return n;
    }
}

const int N = 3000;
const int M = 1000000;

int n, t, m, q;
int a[N + 5], g[N + 5][N + 5];

namespace B {

    const int D = 10;

    int len, ans = 1;
    int v[D + 5][N + 5];
    int e[D + 5][N + 5];
    int o[D + 5][N + 5];
    int p[N + 5][N + 5];
    int gcd[N + 5][N + 5];
    int b[D + 5], d[D + 5];
    vector<int> div[D + 5];

    void clear() {
        ans = 1;
        memset(b, 0, sizeof b);
    }

    void init() {
        for(int i = 0; i <= n; ++i) {
            for(int j = 0; j <= n; ++j) {
                if(!i || !j) gcd[i][j] = i + j;
                else gcd[i][j] = gcd[j % i][i];
            }
        }

        for(int i = t; i >= 1; --i) {
            int x = a[i];
            for(int y = 2; y <= x; ++y) if(x % y == 0) {
                int r = 1;
                while(x % y == 0) x /= y, r *= y;
                d[++ len] = r;
                div[i].push_back(r);
            }
        }

        for(int i = 0; i < n; ++i) {
            int r = i, c = 0;
            for(int j = t; j >= 1; --j) {
                for(auto y : div[j]) {
                    v[++ c][i] = r % a[j] % y;
                }
                r /= a[j];
            }

            p[i][0] = 0;
            for(int j = 1; j <= n; ++j) p[i][j] = g[p[i][j-1]][i];
            for(int j = 1; j <= len; ++j) {

                for(c = 1; v[j][i] * c % d[j]; ++c);
                e[j][i] = p[i][c];

                if(!v[j][i]) continue;

                for(c = 1, r = gcd[v[j][i]][d[j]]; v[j][i] * c % d[j] != r; ++c);
                o[j][i] = p[i][c];
            }
        }
    }

    int tot = 0;
    bool insert(int x) {
        ++ tot;
        if(!x || ans == n) return false;

        bool flag = false;
        for(int i = 1; i <= len; ++i) if(v[i][x]) { 
            if(!b[i]) {
                b[i] = x;
                ans *= d[i] / gcd[d[i]][v[i][x]];
                x = e[i][x];
                flag = true;
            } else {
                int vx = v[i][x], vb = v[i][b[i]];

                if(vx % gcd[vb][d[i]] == 0) {
                    int tmp = (d[i] - vx) / gcd[vb][d[i]];
                    int y = p[o[i][b[i]]][tmp];
                    x = g[x][y];
                } else {
                    ans *= gcd[d[i]][vb] / gcd[d[i]][vx];
                    swap(b[i], x);
                    swap(vx, vb);

                    int tmp = (d[i] - vx) / gcd[vb][d[i]];
                    int y = p[o[i][b[i]]][tmp];
                    x = g[x][y];

                    flag = true;
                    insert(e[i][b[i]]);
                }
            }
        }
        return flag;
    }

    int calc() { return ans; }
}

int v[M + 5], ans[M + 5];
vector<pair<int, int> > que[M + 5];

void input() {
    read(t), read(m), read(q);
    for(int i = 1; i <= t; ++i) read(a[i]);

    n = G::init(t, a, g);
    B::init();

    for(int i = 1; i <= m; ++i) read(v[i]), -- v[i];
    for(int i = 1; i <= q; ++i) {
        static int l, r;
        read(l), read(r);
        que[l].push_back(make_pair(r, i));
    }
}

void solve() {
    static int nxt[M + 5], cur, lst;

    for(int i = m; i >= 1; --i) {
        B::clear();
        nxt[i] = i + 1;
        sort(que[i].begin(), que[i].end());

        cur = lst = i;
        for(auto p : que[i]) {
            while(cur <= p.first) {
                if(!B::insert(v[cur])) {
                    nxt[lst] = nxt[cur]; 
                } else lst = cur;
                cur = nxt[cur];
            }
            ans[p.second] = B::calc();
        }
    }

    for(int i = 1; i <= q; ++i) {
        write(ans[i]);
        putchar('\n');
    }
    cerr << B::tot << endl;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    input();
    solve();

    return 0;
}
