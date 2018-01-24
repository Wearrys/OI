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

template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

const int N = 51;
const int M = 55 * 55;
const int mo = 998244353;

int m, b, c;
int n[N + 5], len;
char num[M + 5], temp[M + 5];

void trans(char* s) {
    int l = strlen(s);

    if(!s[0]) {
        puts("0"); 
        exit(0);
    }

    -- s[l-1];
    for(int i = l-1; s[i] < 0; --i) s[i] += 10, -- s[i-1];

    while(l) {
        int res = 0;
        for(int i = 0; i < l; ++i) 
            res = (res * 10 + s[i] - '0') % b;
        n[len ++] = res; res = 0;

        for(int i = 0; i < l; ++i) {
            res = (res * 10 + s[i] - '0'); 
            temp[i] = (res / b) + '0', res %= b;
        }

        int st = 0, tl = 0;
        while(temp[st] == '0') ++ st;

        for(int i = st; i < l; ++i) s[tl ++] = temp[i];
        l = tl;
    }
}

int s[N + 5][M + 5];

void init() {
    s[0][0] = 1;
    for(int i = 1; i <= N; ++i) {
        for(int j = 0; j <= b-1; ++j) {
            for(int k = j; k <= i*(b-1); ++k) {
                s[i][k] = (s[i][k] + s[i-1][k - j]) % mo;
            }
        }
    }
}

namespace plan0 {
    int dp[N + 5][N + 5][N + 5], x;
    void calc() {
        dp[len][0][0] = 1;
        for(int i = len-1; i >= 0; --i) {
            for(int j = 0; j <= N; ++j) {
                for(int k = 0; k < len-i; ++k) if((x = dp[i+1][j][k]) > 0) {
                    for(int l = 0; l <= N; ++l) {
                        int temp = j*b + n[i]-l, *f = dp[i][l];

                        f[k] = (f[k] + 1ll * s[m-i+1-k][temp] * x) % mo;
                        if(i) {
                            f[k+1] = (f[k+1] + 1ll * s[m-i+1-k][temp-1] * x) % mo;
                        }
                    }
                }
            }
        }
        int res = 0;
        for(int i = 0; i <= N; ++i) res = (res + dp[0][0][i]) % mo;
        printf("%d\n", res);
    }
}

namespace plan1 {
    int dp[N + 5][N + 5];

    void calc() {
        dp[len][0] = 1;
        for(int i = len-1; i >= 0; --i) {
            for(int j = 0; j <= N; ++j) if(dp[i+1][j]) {
                for(int k = 0; k <= N; ++k) {
                    dp[i][k] = (dp[i][k] + 1ll * s[m-i+1][j*b + n[i]-k] * dp[i+1][j]) % mo;
                }
            }
        }
        printf("%d\n", dp[0][0]);
    }
}

void solve() {
    read(m), read(b), read(c);    
    scanf("%s", num); trans(num);

    init();
    (c == 0 ? plan0::calc() : plan1::calc());
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    solve();
    return 0;
}
