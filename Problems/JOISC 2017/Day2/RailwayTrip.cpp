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

const int N = 100000;

int n, k, q;
int a[N + 5];
int L[22][N + 5], R[22][N + 5];

void input() {
    static int stk[N + 5], top;

    read(n); read(k); read(q);
    for(int i = 1; i <= n; ++i) read(a[i]);
    
    stk[top = 1] = 1;
    for(int i = 2; i <= n; ++i) {
        while(top > 1 && a[stk[top]] < a[i]) -- top;
        L[0][i] = stk[top], stk[++ top] = i;
    }

    stk[top = 1] = n;
    for(int i=n-1; i >= 1; --i) {
        while(top > 1 && a[stk[top]] < a[i]) -- top;
        R[0][i] = stk[top], stk[++ top] = i;
    }

    L[0][1] = 1;
    R[0][n] = n;
    for(int j = 1; j < 20; ++j) {
        for(int i = 1; i <= n; ++i) {
            L[j][i] = std::min(L[j-1][L[j-1][i]], L[j-1][R[j-1][i]]);
            R[j][i] = std::max(R[j-1][L[j-1][i]], R[j-1][R[j-1][i]]);
        }
    }
}

void solve() {
    for(int i = 0; i < q; ++i) {
        static int s, t, l, r;
        read(s), read(t);
        if(s > t) std::swap(s, t);

        l = r = s;
        int ans = 0;
        for(int j = 19; j >= 0; --j) {
            int tl = std::min(L[j][l], L[j][r]); 
            int tr = std::max(R[j][l], R[j][r]);

            if(tr < t) {
                l = tl, r = tr;
                ans += (1 << j);
            }
        }

        s = r; l = r = t;
        for(int j = 19; j >= 0; --j) {
            int tl = std::min(L[j][l], L[j][r]); 
            int tr = std::max(R[j][l], R[j][r]);

            if(tl > s) {
                l = tl, r = tr;
                ans += (1 << j);
            }
        }
        printf("%d\n", ans);
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
