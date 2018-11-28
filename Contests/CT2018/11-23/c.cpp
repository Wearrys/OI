#include <bits/stdc++.h>
using namespace std;

const int B = 18;
const int N = 200000;
const int mo = 998244353;

#define fst first
#define snd second

inline void add(int& x, int y) { (x += y) >= mo ? x -= mo : 0; }
inline void sub(int& x, int y) { (x -= y) < 0 ? x += mo : 0; }

template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

int n;
int lg[N + 5];
char s[N + 5];

struct SA {
    int mn[B + 5][N + 5];
    int sa[N + 5], rk[N + 5];
    int c[N + 5], x[N + 5], y[N + 5], h[N + 5];

    void buildsa() {
        int m = 300;
        for(int i = 1; i <= n; ++i) c[x[i] = s[i]] ++;
        for(int i = 1; i <= m; ++i) c[i] += c[i-1];
        for(int i = 1; i <= n; ++i) sa[c[x[i]] --] = i;

        for(int k = 1; k < n; k <<= 1) {
            int p = 0;
            for(int i = n - k + 1; i <= n; ++i) y[++ p] = i;
            for(int i = 1; i <= n; ++i) if(sa[i] > k) y[++ p] = sa[i] - k;

            for(int i = 1; i <= m; ++i) c[i] = 0;
            for(int i = 1; i <= n; ++i) c[x[y[i]]] ++;
            for(int i = 1; i <= m; ++i) c[i] += c[i-1];
            for(int i = n; i >= 1; --i) sa[c[x[y[i]]] --] = y[i];

            p = 0;
            swap(x, y);
            x[sa[1]] = ++ p;
            for(int i = 2; i <= n; ++i) {
                x[sa[i]] = (y[sa[i]] == y[sa[i-1]] && y[sa[i] + k] == y[sa[i-1] + k]) ? p : ++ p;
            }

            if((m = p) == n) break;
        }
    }

    void geth() {
        for(int i = 1; i <= n; ++i) rk[sa[i]] = i;
        for(int i = 1; i <= n; ++i) {
            if(rk[i] == 1) continue;

            int j = sa[rk[i] - 1], k = max(0, h[rk[i - 1]] - 1);
            while(i + k <= n && s[i + k] == s[j + k]) ++ k; 
            
            h[rk[i]] = k;
        }
    }

    void init() {
        buildsa(); geth();

        for(int i = 1; i <= n; ++i) mn[0][i] = h[i];
        for(int i = 1; i <= B; ++i) {
            for(int j = 1; j + (1 << i) - 1 <= n; ++j) {
                mn[i][j] = min(mn[i-1][j], mn[i-1][j + (1 << (i-1))]); 
            }
        }
    }

    int lcp(int l, int r) {
        l = rk[l], r = rk[r]; 
        if(l > r) swap(l, r);
        int k = lg[r - l];
        return min(mn[k][l + 1], mn[k][r - (1 << k) + 1]);
    }
};

SA s0, s1;
bool vis[N * B + 5];
int h[N + 5], f[N + 5], g[N * B + 5];

int cur = 0;
vector<pair<int, int> > mod[N + 5];

void solve() {
    scanf("%s", s + 1); n = strlen(s + 1);
    for(int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
    s0.init(); reverse(s + 1, s + n + 1); s1.init();

    for(int l = 1; l <= n; ++l) h[l] = h[l-1] + n/l;
    for(int l = 1; l <= n; ++l) {
        int L = 0, R = 0;
        for(int i = l + l; i <= n; i += l) if(i > R) {
            R = i + s0.lcp(i, i - l) - 1;
            L = i - l - s1.lcp(n - i + 1, n - (i - l) + 1) + 1;

            if(R - L + 1 < 2 * l || vis[h[l - 1] + (i - l) / l]) continue;

            for(int j = l + l; j + j <= R - L + 1; j += l) {
                vis[h[j - 1] + (L + j - 1) / j] = true;
            }

            int x = cur;
            for(int j = L + (l << 1) - 1; j <= R; ++j) {
                mod[j].push_back(make_pair(x + (j - L + 1) % (l << 1), l));
                if(j < L + (l << 2)) ++ cur;
            }
        }
    }

    int sum = f[0] = 1;
    for(int i = 1; i <= n; ++i) {
        int temp = 0;
        for(auto v : mod[i]) {
            add(g[v.fst], f[i - 2 * v.snd]);
            add(temp, g[v.fst]);
        }
        temp = temp * 2 % mo;
        sub(f[i] = sum, temp);
        add(sum, f[i]);
    }
    printf("%d\n", f[n]);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    solve();
    
    return 0;
}
