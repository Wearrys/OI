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

const int N = 4000;
const int mo = 998244353;

int C[N + 5][N + 5];

void init() {
    for(int i = 0; i <= N; ++i) {
        C[i][0] = C[i][i] = 1;
        for(int j = 1; j < i; ++j) {
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mo;
        }
    }
}

int k, n;
int solve(int x) {
    int tot = 0;
    for(int i = 1; i <= k; ++i) if(x >= i && (x - i) <= k) {
        ++ tot;
    }

    int ans = 0;
    if(x % 2 == 0) {
        -- tot;
        tot /= 2;
        for(int i = 0, pw = 1; i <= tot; ++i, pw = pw * 2 % mo) {
            ans = (ans + (ll) pw * C[tot][i] % mo * C[n+k-2*tot-2][k-2*tot+i-2]) % mo;
            ans = (ans + (ll) pw * C[tot][i] % mo * C[n+k-2*tot-3][k-2*tot+i-2]) % mo;
        }
    } else {
        tot /= 2;
        for(int i = 0, pw = 1; i <= tot; ++i, pw = pw * 2 % mo) {
            ans = (ans + (ll) pw * C[tot][i] % mo * C[n+k-2*tot-1][k-2*tot+i-1]) % mo;
        }
    }
    return ans;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    init();
    read(k), read(n);
    for(int i = 2; i <= 2*k; ++i) {
        printf("%d\n", solve(i));
    }

    return 0;
}
