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

const int N = 60;
typedef unsigned int uint;

uint f(ll x) {
    vector<int> vec;
    static uint dp[N + 5][4][2];

    ++ x;
    while(x > 0) vec.pb(x & 1), x >>= 1;

    memset(dp, 0, sizeof dp);
    dp[0][0][0 >= vec[0]] = -1;
    dp[0][1][1 >= vec[0]] = 1;

    int len = (int) vec.size();
    for(int i = 0; i < len - 1; ++i) {
        for(int j = 0; j < 4; ++j) {
            for(int k = 0; k < 2; ++k) {
                dp[i + 1][(j >= 2) ? j ^ 1 : j + 1][(!vec[i+1]) | (vec[i+1] & k)] += dp[i][j][k];

                if(j == 0) {
                    dp[i + 1][j][(vec[i+1] == 0) & k] -= dp[i][j][k];
                } else {
                    dp[i + 1][1][(vec[i+1] == 0) & k] += (j == 3) ? -dp[i][j][k] : dp[i][j][k];
                }
            }
        }
    }

    uint ans = 0;
    for(int i = 1; i <= 3; ++i) {
        ans += (i == 3) ? -dp[len - 1][i][0] : dp[len - 1][i][0];
    }
    return ans;
}

int g(ll x) {
    int y = 0, res = 1;
    while(x > 0) {
        if(x & 1) ++ y;
        else {
            if(y == 0) res *= -1;
            else {
                if((y & 1) && y > 1) res *= -1;
                y = 1;
            }
        } x >>= 1;
    }
    if((y & 1) && y > 1) res *= -1;
    return res;
}

ll n;
int T, op;

int main() {
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);

    read(T);
    while(T--) {
        read(op), read(n);
        if(op == 1) printf("%d\n", g(n));
        if(op == 2) printf("%u\n", f(n));
    }

    return 0;
}
