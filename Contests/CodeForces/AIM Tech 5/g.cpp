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

const ll M = 10004205361450474ll;

vector <ll> vec;
int query() {
    printf("%d ", (int) vec.size()); 
    for(auto v : vec) printf("%lld ", v);
    puts(""); fflush(stdout); 
    static int op; scanf("%d", &op);
    return op;
}

const int N = 10000;

ll step[6];
ll dp[10005][6];

ll get(ll x, int p) {
    if(x >= N) return x + step[p] - 1;
    if(p == 1) return x + x - 1;
    if(dp[x][p] > 0) return dp[x][p];

    ll r = get(x, p - 1) + 1;
    for(int i = 1; i <= x; ++i) {
        r = get(r + 1, p - 1) + 1;
    }
    return dp[x][p] = r - 1;
}

void solve(ll l, ll r, int s = 5) {

    vec.clear();
    if(l >= N) {
        ll p = get(l, s - 1) + 1;
        for(int i = 1; i <= N; ++i) {
            vec.pb(p);
            p = get(p + 1, s - 1) + 1;
        }
    } else {
        if(s == 1) {
            for(int i = l; i <= r; ++i) vec.pb(i);
        } else {
            ll p = get(l, s - 1) + 1;
            for(int i = 1; i <= l; ++i) {
                vec.pb(p); 
                p = get(p + 1, s - 1) + 1;
            }
        }
    }

    int x = query();
    if(x == -1) exit(0);
    if(x == 0) solve(l, vec[0] - 1, s - 1);
    if(x == (int) vec.size()) solve(vec.back() + 1, r, s - 1);
    solve(vec[x - 1] + 1, vec[x] - 1, s - 1);
}

int main() {
#ifdef Wearry
    //freopen("in", "r", stdin);
    //freopen("out", "w", stdout);
#endif

    for(int i = 1; i <= 5; ++i) 
        step[i] = step[i-1] * (N + 1) + N;

    solve(1, M);

    return 0;
}
