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

const int N = 15;
const int S = 1 << 14;

const int l[] = { 0, 1, 3, 7 };
const int r[] = { 0, 2, 6, 14 };

inline bool chk1(int i, int s) {
    for (int j = 0; j < 4; ++ j) if(r[j] < i) {
        bool ret = 0;
        for (int k = l[j]; k <= r[j]; ++ k) ret ^= (s >> k & 1);
        if (ret) return true;
    }
    return false;
}

inline bool chk2(int i, int s) {
    bool ret = 0;
    for (int j = 0; j < 4; ++ j) {
        if(r[j] < i) 
            for (int k = l[j]; k <= r[j]; ++ k) ret ^= (s >> k & 1);
        if(l[j] > i) 
            for (int k = l[j]; k <= r[j]; ++ k) ret ^= (s >> (k - 1) & 1);
    }
    return ret;
}

ll C(int n, int k) {
    ll res = 1;
    for (int i = n; i > k; -- i) res *= i;
    for (int i = 1; i <= n-k; ++ i) res /= i;
    return res;
}

ll fac(int n) {
    ll res = 1;
    for (int i = 1; i <= n; ++ i) res *= i;
    return res;
}


int main() {

    FILE *outp1 = fopen("vote1.ans", "w");
    FILE *outp2 = fopen("vote2.ans", "w");
    FILE *outp3 = fopen("vote3.ans", "w");
    FILE *outp4 = fopen("vote4.ans", "w");

    int pw2 = 1;

    for (int i = 0; i < N; ++i) {

        for (int j = 0; j < S; ++j) {
            int b = __builtin_popcount(j);

            if (chk1(i, j)) {
                fprintf(outp1, (i & 1) ? "1" : "0");
                fprintf(outp2, (i & 1) ? "1" : "0");
            } else {
                fprintf(outp1, (chk2(i, j) & 1) ? "0" : "1");
                fprintf(outp2, (chk2(i, j) & 1) ? "0" : "1");
            }

            if (j & (pw2 - 1)) {
                fprintf(outp3, "0 ");
            } else {
                fprintf(outp3, (b & 1) ? "-%d " : "%d ", pw2);
            }

        }

        pw2 <<= 1;
        fprintf(outp1, "\n");
        fprintf(outp2, "\n");
        fprintf(outp3, "\n");
    }

    int t = 5;
    static ll poly[N + 5], res[N + 5], ans[N + 5];

    poly[0] = 1;
    for (int i = 0; i < 7; ++i) {
        for (int j = i+1; j >= 0; --j) {
            poly[j] = poly[j] * t + (j ? -2 * poly[j-1] : 0);
        }
        t += 2;
    }
    for (int i = 0; i <= 7; ++i) poly[i] = - poly[i];

    static ll dp[N + 5][N + 5];

    dp[0][0] = 1;
    for (int i = 1; i <= 7; ++ i) {
        for (int j = 0; j <= 12; ++ j) {
            dp[i][j] = (dp[i-1][j] * j) + (j ? dp[i-1][j-1] : 0) * (12-j+1);
        }
    }

    res[0] = poly[0];
    for (int i = 7; i >= 1; --i) {
        for (int j = i; j <= 7; ++j) {
            res[i] += dp[j][i] * poly[j];
        }
    }

    for (int i = 0; i <= 12; ++i) {
        ll tmp = 0, t2 = 0, x = 1;
        for (int j = 0; j <= i; ++j) tmp += res[j] * C(i, j) / C(12, j);
        for (int j = 0; j <= 7; ++j) { t2 += poly[j] * x; x *= i; }
    }

    for (int i = 0; i <= 7; ++i) {
        ans[i] = res[i];
        for (int j = 0; j < i; ++j) {
            ans[i] -= ans[j] * C(7-j, i-j) * ((i-j) % 2 ? -1 : 1);
        }
    }

    for (int i = 0; i < 792; ++ i) {
        for (int j = 0; j < (1 << 7); ++ j) {
            int y = __builtin_popcount(j);
            fprintf(outp4, "%lld ", ans[y] / C(12, 7) / C(7, y));
        }
        fprintf(outp4, "\n");
    }

    return 0;
}
