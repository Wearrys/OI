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

const int N = 500000;

inline int max(int x, int y) { return x > y ? x : y; }
inline int min(int x, int y) { return x < y ? x : y; }

int n, m; 
vector<int> keys[N + 5];
int c[N + 5], L[N + 5], R[N + 5], lg[N + 5];
int mn[N + 5][20], mx[N + 5][20], lst[N + 5];

inline int query_mx(int l, int r) {
    if(l > r) return -oo;
    int k = lg[r - l + 1];
    return max(mx[l][k], mx[r - (1 << k) + 1][k]);
}

inline int query_mn(int l, int r) {
    if(l > r) return oo;
    int k = lg[r - l + 1];
    return min(mn[l][k], mn[r - (1 << k) + 1][k]);
}

void input() {
    read(n);
    for(int i = 1; i < n; ++i) read(c[i]);
    for(int i = 1; i <= n; ++i) {
        int x, y;
        for(read(x); x--; ) keys[i].pb(read(y));
    }

    memset(lst, 0, sizeof lst);
    for(int i = 1; i < n; ++i) {
        for(auto x : keys[i]) lst[x] = i;
        mn[i][0] = lst[c[i]];
    }

    memset(lst, 0x3f, sizeof lst);
    for(int i = n; i > 1; --i) {
        for(auto x : keys[i]) lst[x] = i;
        mx[i-1][0] = lst[c[i-1]];
    }

    for(int i = 2; i <= N; ++i) lg[i] = lg[i >> 1] + 1;
    for(int j = 1; j < 20; ++j) {
        for(int i = 1; i + (1 << j) <= n; ++i) {
            mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
            mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
        }
    }
}

void solve() {
    for(int i = 1; i <= n; ++i) {
        if(R[i-1] >= i) {
            int l = i, r = R[i-1];
            while(l < r) {
                int mid = (l + r + 1) >> 1;
                if(query_mn(i, mid - 1) >= i) l = mid; else r = mid - 1;
            }

            if(mx[i-1][0] <= l) {
                L[i] = L[i-1];
                R[i] = R[i-1];
            } else {
                L[i] = i;
                R[i] = l;
            }
        } else {
            int l = i, r = n;
            while(l < r) {
                int mid = (l + r + 1) >> 1;
                if(query_mn(i, mid - 1) >= i) l = mid; else r = mid - 1;
            }

            L[i] = i, R[i] = l;
            
            while(true) {
                l = 1, r = L[i];
                while(l < r) {
                    int mid = (l + r) >> 1;
                    if(query_mx(mid, L[i] - 1) <= R[i]) r = mid; else l = mid + 1;
                }
                if(l == L[i]) break; else L[i] = l;

                l = R[i], r = n;
                while(l < r) {
                    int mid = (l + r + 1) >> 1;
                    if(query_mn(R[i], mid - 1) >= L[i]) l = mid; else r = mid - 1;
                }
                if(l == R[i]) break; else R[i] = l;
            }
        }
    }

    read(m);
    while(m--) {
        static int s, t;
        read(s), read(t);
        puts(L[s] <= t && t <= R[s] ? "YES" : "NO");
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    input();
    solve();

    return 0;
}
