#include <bits/stdc++.h>
using namespace std;

const int N = 8000;
const int mo = 998244353;

inline void add(int& x, int y) { (x += y) >= mo ? x -= mo : 0; }
inline void sub(int& x, int y) { (x -= y) < 0 ? x += mo : 0; }

template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

int n;
ull hs[N + 5];
ull pw[N + 5];
char st[N + 5];
int rep[N + 5][N + 5];

void init_hash() {
    pw[0] = 1;
    for(int i = 1; i <= n; ++i) pw[i] = pw[i-1] * 29;
    for(int i = 1; i <= n; ++i) hs[i] = hs[i-1] * 29 + st[i] - 'a';
}

inline ull get_hash(int l, int r) {
    return hs[r] - hs[l-1] * pw[r - l + 1];
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%s", st + 1);
    n = strlen(st + 1);

    if(n > 8000) return 0;

    init_hash();

    for(int i = 1; i <= n; ++i)
        for(int j = i; j <= n; ++j) rep[i][j] = 1;
    for(int i = 1; i <= n; ++i) {
        for(int d = 1; i + d*2 - 1 <= n; ++d) {
            ull cur = get_hash(i, i + d - 1);
            for(int j = i + d, c = 2; d + j - 1 <= n; j += d, ++c) {
                if(cur == get_hash(j, j + d - 1)) {
                    chkmax(rep[i][j + d - 1], c);
                } else break;
            }
        }
    }

    static int dp[N + 5];

    dp[0] = 1;
    for(int i = 1; i <= n; ++i) {
        for(int j = i - 1; j >= 0; --j) {
            add(dp[i], (rep[j + 1][i] & 1) ? dp[j] : mo - dp[j]);
        }
    }
    printf("%d\n", dp[n]);
    
    return 0;
}
