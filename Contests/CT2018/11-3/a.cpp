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

const int N = 50;

int ans;
int n, R;
char st[N + 5];
ll binom[N + 5][N + 5];

void init() {
    for(int i = 0; i <= N; ++i) {
        binom[i][i] = binom[i][0] = 1;
        for(int j = 1; j < i; ++j) {
            binom[i][j] = binom[i-1][j] + binom[i-1][j-1];
        }
    }
}

vector<int> vec;
std::set<int> s[2];

void chk() {
    s[0].clear(), s[1].clear();
    for(int i = 0; i < n; ++i) if(st[i] == 'o') {
        s[0].insert(i);
    } else {
        s[1].insert(i);
    }

    if((int) s[0].size() > (int) s[1].size()) {
        int turn = 0;
        while(*(s[0].rbegin()) > *(s[1].begin())) {
            if(!turn) {
                s[1].erase(*s[1].begin());
            } else {
                s[0].erase(s[0].upper_bound(*s[1].begin()));
            } turn ^= 1;
        }
    } else {
        int turn = 0;
        while(*(s[0].rbegin()) > *(s[1].begin())) {
            if(!turn) {
                s[1].erase(-- s[1].lower_bound(*s[0].rbegin()));
            } else {
                s[0].erase(s[0].upper_bound(*s[1].begin()));
            } turn ^= 1;
        }
    }

    if((int) s[0].size() > (int) s[1].size()) {
        ans += ((int) s[0].size() >= R);
    }
}

void dfs(int cur) {
    if(cur == (int) vec.size()) {
        chk();
        return;
    }
    st[vec[cur]] = 'o';
    dfs(cur + 1);
    st[vec[cur]] = 'x';
    dfs(cur + 1);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    init();
    scanf("%s%d", st, &R);

    n = strlen(st);
    for(int i = 0; i < n; ++i) {
        if(st[i] == '?') {
            vec.pb(i);
        }
    }

    if((int) vec.size() <= 18) { dfs(0); printf("%d\n", ans); } else 
    {
        ll res = 0;
        static ll dp[N + 5][N + 5][N + 5][N + 5];

        dp[0][0][0][0] = 1;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j <= i; ++j) {
                for(int k = 0; k <= i; ++k) {
                    for(int l = 0; l <= i; ++l) {
                        if(k == 0) {
                            if(st[i] == 'o' || st[i] == '?') dp[i + 1][j + 1][k][l] += dp[i][j][k][l];
                            if(st[i] == 'x' || st[i] == '?') dp[i + 1][j][j][l] += dp[i][j][k][l];
                        } else {
                            if(st[i] == 'o' || st[i] == '?') dp[i + 1][j + 1][k][l + (i - j > l + 1)] += dp[i][j][k][l];
                            if(st[i] == 'x' || st[i] == '?') dp[i + 1][j][k][l] += dp[i][j][k][l];
                        }
                    }
                }
            }
        }

        for(int i = 0; i <= n; ++i) if(i > n - i) {
            for(int j = 0; j <= n; ++j) {
                for(int k = 0; k <= i; ++k) if(dp[n][i][j][k] > 0) {
                    res += dp[n][i][j][k] * (i - k >= R);
                }
            }
        }

        for(int l = 0; l < n && st[l] != 'x'; ++l) if(st[l + 1] == '?' || st[l + 1] == 'x') {
            for(int r = n - 1; r-1 > l+1 && st[r] != 'o'; --r) if(st[r - 1] == '?' || st[r - 1] == 'o') {
                int co = 1, cx = 1, t = 0;
                for(int i = l + 2; i < r - 1; ++i) {
                    co += st[i] == 'o';
                    cx += st[i] == 'x';
                    t += st[i] == '?';
                }

                if((cx + n - r + t - co - l - 1) % 2) continue;

                int so = (cx + n - r + t - co - l - 1) / 2; 
                ll temp = binom[t][so];

                co += so, cx += t - so;

                int ro = (co >= cx ? co - (cx - 1) : 0);
                int rx = (co >= cx ? 0 : cx - co);

                if(ro + l + 1 > rx + (n - r)) {
                    res += (ro + l + 1 >= R) * temp;
                }
            }
        }

        printf("%lld\n", res);
    }

    return 0;
}
