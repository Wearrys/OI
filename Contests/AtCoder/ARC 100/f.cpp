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

const int K = 400;
const int N = 25000;
const int mo = 1e9 + 7;

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = (ll) res * x % mo;
        x = (ll) x * x % mo;
    }
    return res;
}

int n, k, m;
int a[N + 5];
int vis[N + 5];

int chk() {
    int p = 1, flag = 0;
    for(int i = 1; i <= m; ++i) {
        if(vis[a[i]]) {
            flag = true;
            chkmax(p, vis[a[i]]);
        }
        if(i - p == k) return 1;
        vis[a[i]] = i;
    }
    return flag ? 0 : 2;
}

void get_range(int& x, int& y) {
    x = y = 0;
    memset(vis, 0, sizeof vis);
    for(int i = 1; i <= m; ++i) {
        if(vis[a[i]]) break;    
        vis[a[i]] = true, ++ x;
    }

    memset(vis, 0, sizeof vis);
    for(int i = m; i >= 1; --i) {
        if(vis[a[i]]) break;
        vis[a[i]] = true, ++ y;
    }
}

int s[N + 5][K + 5], t[N + 5][K + 5];
int f[N + 5][K + 5], g[N + 5][K + 5];

void init(int x, int y) {
    f[x][x] = 1; g[y][y] = 1;
    for(int i = 0; i <= x; ++i) s[x][i] = 1;
    for(int i = 0; i <= y; ++i) t[y][i] = 1;
    for(int i = x + 1; i <= n; ++i) {
        for(int j = 1; j < k; ++j) {
            f[i][j] = (ll) f[i-1][j-1] * (k-j+1) % mo;
            f[i][j] = (f[i][j] + s[i-1][j]) % mo;
        }
        for(int j = k-1; j >= 0; --j) {
            s[i][j] = (s[i][j+1] + f[i][j]) % mo;
        }
    }
    for(int i = y + 1; i <= n; ++i) {
        for(int j = 1; j < k; ++j) {
            g[i][j] = (ll) g[i-1][j-1] * (k-j+1) % mo;
            g[i][j] = (g[i][j] + t[i-1][j]) % mo;
        }
        for(int j = k-1; j >= 0; --j) {
            t[i][j] = (t[i][j+1] + g[i][j]) % mo;
        }
    }
}

int calc() {
    f[0][0] = 1;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j < k; ++j) {
            f[i][j] = (ll) f[i-1][j-1] * (k-j+1) % mo;
            f[i][j] = (f[i][j] + s[i-1][j]) % mo;

            g[i][j] = (ll) g[i-1][j-1] * (k-j+1) % mo;
            g[i][j] = (g[i][j] + t[i-1][j]) % mo;
            g[i][j] = (g[i][j] + (j >= m) * f[i][j]) % mo;
        }
        for(int j = k-1; j >= 0; --j) {
            s[i][j] = (s[i][j+1] + f[i][j]) % mo;
            t[i][j] = (t[i][j+1] + g[i][j]) % mo;
        }
    }
    int res = 0;
    for(int i = 0; i < k; ++i) res = (res + g[n][i]) % mo;
    for(int i = 0; i < m; ++i) res = (ll) res * fpm(k - i, mo - 2) % mo;
    return res;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(k), read(m);
    for(int i = 1; i <= m; ++i) read(a[i]);
    int ans = (ll) (n - m + 1) * fpm(k, n - m) % mo;
    int cid = chk();

    if(cid == 1) {
        printf("%d\n", ans);
    } else if(cid == 2) {
        ans = (ans - calc() + mo) % mo;
        printf("%d\n", ans);
    } else {
        static int x, y;
        get_range(x, y); init(x, y);
        for(int i = 1; i <= n - m + 1; ++i) {
            ans = (ans - (ll) s[x + i - 1][0] * t[n - i - m + 1 + y][0]) % mo;
        }
        ans = (ans + mo) % mo;
        printf("%d\n", ans);
    }
    return 0;
}

