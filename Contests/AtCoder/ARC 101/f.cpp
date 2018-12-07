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
const int mo = 1e9 + 7;

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

const int N = 200000;

int n, m;
int x[N + 5], y[N + 5], c[N + 5];

void add(int x, int y) {
    ++ x;
    while(x <= N) {
        c[x] = (c[x] + y) % mo; 
        x += (x & -x);
    }
}
int query(int x) {
    int res = 0;
    ++ x;
    while(x > 0) {
        res = (res + c[x]) % mo;
        x -= (x & -x);
    }
    return res;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(m);
    for(int i = 1; i <= n; ++i) read(x[i]);
    for(int i = 1; i <= m; ++i) read(y[i]);

    int l = 1, r = n;
    while(l <= n && x[l] < y[1]) ++ l;
    while(r >= 1 && x[r] > y[m]) -- r;

    if(l > r) return puts("1"), 0;

    vector<int> d;
    vector<pii> vec;

    for(int i = l; i <= r; ++i) {
        int lst = std::upper_bound(y + 1, y + m + 1, x[i]) - y - 1;
        int nxt = std::lower_bound(y + 1, y + m + 1, x[i]) - y;

        d.pb(y[nxt] - x[i]);
        vec.pb(mp(x[i] - y[lst], y[nxt] - x[i]));
    }

    std::sort(d.begin(), d.end());
    std::sort(vec.begin(), vec.end());

    d.erase(std::unique(d.begin(), d.end()), d.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());

    add(0, 1);
    for(int i = 0; i < (int) vec.size(); ++i) {
        int j = i;
        while(j + 1 < (int) vec.size() && vec[j + 1].fst == vec[i].fst) {
            ++ j;
        }
        for(int k = j; k >= i; --k) {
            int id = std::lower_bound(d.begin(), d.end(), vec[k].snd) - d.begin() + 1;
            add(id, query(id-1));
        }
        i = j;
    }
    printf("%d\n", query(N));

    return 0;
}
