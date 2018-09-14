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

const int M = 500000;

ll n;
bool notprime[M + 5];
vector<int> pris[M + 5];

inline int f(int l, int r, int x) {
    -- l;
    return (r / x) - (l / x);
}

void init() {
    for(int i = 2; i <= M; ++i) if(!notprime[i]) {
        for(int j = i; j <= M; j += i) {
            notprime[j] = true;
            pris[j].pb(i);
        }
    }
}

bool chk(int x, int y) {
    for(auto p : pris[x]) if(y % p == 0) return false;
    return true;
}

int main() {
    //freopen("calc.in", "r", stdin);
    //freopen("calc.out", "w", stdout);

    init();
    read(n);
    int m = (int) sqrt(n + 0.5);

    ll ans = 0;
    for(int p = 2; p <= m; ++p) {
        int T = n / p, L = pris[p].size();
        int K = (int) sqrt(1. * (T << L) / L + 0.5);

        static int mul[1 << 20];
        for(int i = 0; i < (1 << L); ++i) {
            mul[i] = 1;
            for(int j = 0; j < L; ++j) if(i >> j & 1) mul[i] *= pris[p][j];
        }

        chkmin(K, 2*p-1);
        chkmax(K, p+1);

        for(int q = p + 1; q <= K; ++q) if(chk(p, q)) { ans += (T / q); }
        for(int q = K + 1; q <= 2*p-1 && q <= T; ) {
            int nxt = std::min(2*p-1, T / (T / q)), res = 0;

            for(int i = 0; i < (1 << L); ++i) {
                if(__builtin_popcount(i) & 1)
                    res = res - f(q, nxt, mul[i]);
                else 
                    res = res + f(q, nxt, mul[i]);
            }

            ans += res * (T / q);
            q = nxt + 1;
        }
    }
    printf("%lld\n", ans);

    return 0;
}
