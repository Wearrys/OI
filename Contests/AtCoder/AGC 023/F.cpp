#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)

template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;

inline void read(int& x) {
    x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar());
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
}

const int N = 500000;

string procStatus() {
    ifstream t("/proc/self/status");
    return string(istreambuf_iterator<char>(t), istreambuf_iterator<char>());
}

int n;
int a[N + 5], w[N + 5];

int fa[N + 5];
int find(int x) {
    return (x == fa[x]) ? x : fa[x] = find(fa[x]);
}

struct node {
    int sz0, sz1, id;

    node() { }
    node(int s0, int s1, int _id): sz0(s0), sz1(s1), id(_id) { }

    inline bool operator < (const node& b) const {
        return (ll) sz1 * b.sz0 > (ll) b.sz1 * sz0;
    }
};

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    for(int i = 2; i <= n; ++i) read(a[i]);
    for(int i = 1; i <= n; ++i) read(w[i]);
    
    static node q[N + 5];
    static node cur[N + 5];

    int cnt = 0;
    for(int i = 1; i <= n; ++i) fa[i] = i;
    for(int i = 1; i <= n; ++i) {
        cur[i] = node((w[i] == 0), (w[i] == 1), i);
        if(i > 1) q[++ cnt] = cur[i];
    }

    make_heap(q + 1, q + cnt + 1);

    ll ans = 0;
    while(cnt) {
        node temp = q[1]; 
        pop_heap(q + 1, q + cnt-- + 1);
        if(temp.sz0 != cur[temp.id].sz0 || temp.sz1 != cur[temp.id].sz1) continue; 

        int u = temp.id, f = find(a[u]);

        fa[u] = f;
        ans += (ll) cur[f].sz1 * temp.sz0;
        cur[f] = node(temp.sz0 + cur[f].sz0, temp.sz1 + cur[f].sz1, f);

        if(f) { 
            q[++ cnt] = cur[f]; 
            push_heap(q + 1, q + cnt + 1); 
        }
    }
    printf("%lld\n", ans);

    return 0;
}
