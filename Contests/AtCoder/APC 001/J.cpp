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

const int N = 200;
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

int solve(int a, int A, int b, int B) {
    int res = 0;
    res = (res + (ll) fpm(a, B / b) * b) % mo;
    res = (res + (ll) fpm(b, A / a) * a) % mo;
    res = (res - (ll) a * b) % mo;
    return res;
}

int solve(int a, int A, int b, int B, int c, int C) {
    int res = 0;
    res = (res + (ll) fpm(solve(b, B, c, C), A / a) * a) % mo;
    res = (res + (ll) fpm(solve(a, A, c, C), B / b) * b) % mo;
    res = (res + (ll) fpm(solve(a, A, b, B), C / c) * c) % mo;
    res = (res - (ll) fpm(a, (B / b) * (C / c)) * b * c) % mo;
    res = (res - (ll) fpm(b, (A / a) * (C / c)) * a * c) % mo;
    res = (res - (ll) fpm(c, (A / a) * (B / b)) * a * b) % mo;
    res = (res + (ll) a * b * c) % mo;
    return res;
}

int ans;
int a, b, c, A, B, C;
int f[N + 5][N + 5], binom[N + 5][N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(a), read(b), read(c), read(A), read(B), read(C);

    if(A % a || B % b || C % c) return puts("0"), 0;

    ans = solve(a, A, b, B, c, C);

    for(int i = 0; i <= N; ++i) {
        binom[i][0] = binom[i][i] = 1;
        for(int j = 1; j < i; ++j) {
            binom[i][j] = (binom[i-1][j] + binom[i-1][j-1]) % mo;
        }
    }

    int ma = A / a, mb = B / b;

    for(int i = ma; i > 0; --i) {
        for(int j = mb; j > 0; --j) {
            f[i][j] = (ll) binom[ma][i] * binom[mb][j] % mo * fpm(c, (ma - i) * (mb - j)) % mo;

            for(int k = i; k <= ma; ++k)
                for(int l = j; l <= mb; ++l) if(k > i || l > j) {
                    f[i][j] = (f[i][j] - (ll) f[k][l] * binom[k][i] % mo * binom[l][j]) % mo;
                }

            if(i < ma || j < mb) {
                int res = 1;
                res = (res + fpm((fpm(b, i) + fpm(a, j) - 1) % mo, C / c)) % mo;
                res = (res - fpm(fpm(b, i), C / c)) % mo;
                res = (res - fpm(fpm(a, j), C / c)) % mo;
                res = (ll) res * a * b * c % mo;
                ans = (ans + (ll) res * f[i][j]) % mo;
            }
        }
    }

    ans = (ans + mo) % mo;
    printf("%d\n", ans);

    return 0;
}
