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

const int N = 3000;

int fpm(int x, int y, int mo) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = (ll) res * x % mo;
        x = (ll) x * x % mo;
    }
    return res;
}

int n, mo;
int pw[N * N + 5];
int c[N + 5][N + 5], f[N + 5][N + 5];

void init() {
    pw[0] = 1;
    for(int i = 1; i <= N*N; ++i) pw[i] = (pw[i-1] << 1) % mo;
        
    for(int i = 0; i <= N; ++i) {
        c[i][0] = c[i][i] = 1;
        f[i][0] = 1, f[i][i] = 1;

        for(int j = 1; j < i; ++j) {
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mo;
            f[i][j] = ((ll) f[i-1][j] * (j + 1) + f[i-1][j-1]) % mo;
        }
    }
}

int calc(int x) {
    int ans = 0, coe = fpm(2, fpm(2, n - x, mo - 1), mo);

    for(int z = 0; z <= x; ++z) {
        ans = (ans + (ll) coe * f[x][z] % mo * pw[(n - x) * z]) % mo;
    }
    return ans;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(mo); init();

    int ans = 0, sgn = 1;
    for(int i = 0; i <= n; ++i) {
        int coe = (ll) sgn * c[n][i] % mo;
        ans = (ans + (ll) coe * calc(i)) % mo;
        sgn = mo - sgn;
    }
    printf("%d\n", ans);

    return 0;
}
