#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back
#define mp std::make_pair
#define debug(...) fprintf(stderr, __VA_ARGS__)

template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;

template <typename T> T read(T& x) {
    T f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = 4000;

int n;
vector<int> G[N + 5];
int fa[N + 5], a[N + 5];
int r[N + 5], b[N + 5], d[N + 5];

bool chk() {
    for(int i = 0; i < n; ++i) if(a[i] != i) return false;
    return true;
}

vector<int> ans;
void move(int u) {
    ans.pb(u);
    int t = a[0];
    for(int i = u; i >= 0; i = fa[i]) std::swap(a[i], t);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);

    fa[0] = -1;
    for(int i = 1; i < n; ++i) read(fa[i]), G[fa[i]].pb(i), d[i] = d[fa[i]] + 1;
    for(int i = 0; i < n; ++i) read(a[i]);

    int cnt = 0;
    while(cnt < n) {
        vector<int> trash;
        for(int i = n - 1; i >= 0; --i) if(!b[i]) {
            trash.pb(i);
            int c = -1, sz = 0;
            for(auto v : G[i]) if(!b[v]) ++ sz, c = v;

            if(!sz) r[i] = i;
            else if(sz == 1 && r[c] != -1) r[i] = r[c];
            else r[i] = -1;
        }

        std::sort(trash.begin(), trash.end(), [&](const int& p, const int& q) {
            return mp(r[p], d[p]) > mp(r[q], d[q]);
        });

        for(int i = 0; i < (int) trash.size(); ) {
            if(r[a[0]] != -1) {
                int x = r[a[0]];
                for(; b[x] && a[x] > a[0]; x = fa[x]);
                move(x);
                ++ cnt;
                for(; b[x]; x = fa[x]); 
                b[x] = true;
            } else {
                move(trash[i++]);
            }
            for(; i < (int) trash.size() && b[trash[i]]; ++i);
        }
    }

    assert(chk());
    printf("%lu\n", ans.size());
    for(auto v : ans) printf("%d\n", v);

    return 0;
}
