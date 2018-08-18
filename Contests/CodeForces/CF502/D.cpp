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

template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;

template<typename T> T read(T& x) {
    T f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = 500000;
const int S = 1 << 12;

int n, m, q;
int w[N + 5];
int cnt[S], ans[N + 5];
char st[N + 5];

vector<pii> Q[S];
pair<int, int> sum[S];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(m), read(q);
    for(int i = 0; i < n; ++i) read(w[i]);
    for(int i = 0; i < m; ++i) {
        int cur = 0; scanf("%s", st);
        for(int j = 0; j < n; ++j) cur += (st[j] - '0') << j;
        ++ cnt[cur];
    }
    for(int i = 0; i < q; ++i) {
        int cur = 0, k;
        scanf("%s", st), read(k);
        for(int j = 0; j < n; ++j) cur += (st[j] - '0') << j;
        Q[cur].pb(mp(k, i));
    }

    int all = (1 << n);
    for(int i = 0; i < all; ++i) {
        sum[i].snd = i;
        for(int j = 0; j < n; ++j) if(!(i >> j & 1)) sum[i].fst += w[j];
    }

    std::sort(sum, sum + all);
    
    for(int i = 0; i < all; ++i) {
        int j = 0, s = 0;
        std::sort(Q[i].begin(), Q[i].end());

        for(auto v : Q[i]) {
            while(j < all && sum[j].fst <= v.fst) {
                s += cnt[i ^ sum[j].snd];
                ++ j;
            } ans[v.snd] = s;
        }
    }
    for(int i = 0; i < q; ++i) printf("%d\n", ans[i]);

    return 0;
}
