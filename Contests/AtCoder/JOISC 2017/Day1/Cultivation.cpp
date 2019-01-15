#include <bits/stdc++.h>

using std::pair;
using std::vector;
using std::string;

typedef long long ll;
typedef pair<ll, int> pli;
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

const int N = 600;

int r, c, n;
struct point { int x, y; } p[N + 5];

inline bool cmpx (const point& a, const point& b) { return a.x < b.x; }
inline bool cmpy (const int& a, const int& b) { return p[a].y < p[b].y; }

void input() {
    read(r), read(c), read(n);
    for(int i = 1; i <= n; ++i) {
        read(p[i].x), read(p[i].y);
    }
    std::sort(p + 1, p + n + 1, cmpx);
}

int id[N + 5];
bool mark[N + 5][N + 5];
int L[N + 5], C[N + 5], R[N + 5];

void insert(int x, int y) {
    mark[x][y] = true;

    C[x] = R[x] = -1;
    for(int i = 1; i <= n; ++i) if(mark[x][y = id[i]]) {
        if(!~R[x]) {
            L[x] = p[y].y - 1;
        } else chkmax(C[x], p[y].y - R[x] - 1);

        R[x] = p[y].y;
    }
    R[x] = c - R[x];
}

pli q[N + 5], t[N + 5];

struct deque {
    int que[N + 5];
    int head, tail;

    inline void clear() { head = tail = 0; }
    inline void pop(int x) { 
        while(head < tail && q[que[head]].fst < q[x].fst)
            ++ head;
    }
    inline void push(int x, int *y) {
        while(head < tail && y[q[que[tail-1]].snd] <= y[q[x].snd])
            -- tail;

        que[tail ++] = x;
    }

    inline int operator [] (int *y) { return y[q[que[head]].snd]; }
};

int calc() {
    int res = oo << 1;
    static deque que[3];
    std::merge(t + 1, t + n + 1, t + n + 1, t + 2*n + 1, q + 1);

    int j = 1;
    for(int i = 0; i < 3; ++i) que[i].clear();
    for(int i = 1; i <= 2*n && q[i].fst + r <= q[2*n].fst; ++i) {
        for(int k = 0; k < 3; ++k) que[k].pop(i);

        while(j <= 2*n && q[i].fst + r > q[j].fst) {
            que[0].push(j, L); que[1].push(j, C); que[2].push(j, R);
            ++ j;
        }

        chkmin(res, std::max(que[0][L] + que[2][R], que[1][C]));
    }
    return res;
}

void solve() {
    static int len[N * N << 1], cnt;
    
    len[++ cnt] = p[1].x + r - 1 - p[n].x;
    for(int i = 2; i <= n; ++i) chkmax(len[cnt], p[i].x - p[i-1].x - 1);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) if(j != i) {
            if(p[i].x + r - 1 - p[j].x > len[1]) {
                len[++ cnt] = p[i].x + r - 1 - p[j].x;
            }
            if(i < j && p[j].x - p[i].x - 1 > len[1]) {
                len[++ cnt] = p[j].x - p[i].x - 1;
            }
        }
    }

    std::sort(len + 1, len + cnt + 1);
    cnt = std::unique(len + 1, len + cnt + 1) - len - 1;

    for(int i = 1; i <= n; ++i) id[i] = i;
    std::sort(id + 1, id + n + 1, cmpy); 

    ll ans = LLONG_MAX;
    static int tx[N + 5], ty[N + 5];
    for(int i = 1; i <= n; ++i) tx[i] = ty[i] = 1;
    for(int i = 1; i <= cnt; ++i) {
        for(int j = 1; j <= n; ++j) {
            for(; tx[j] <= n && p[j].x + len[i] >= p[tx[j]].x; ++ tx[j])
                if(p[j].x <= p[tx[j]].x) insert(tx[j], j);
            for(; ty[j] <= n && p[j].x + len[i] + 1 >= p[ty[j]].x; ++ ty[j]) 
                if(p[j].x < p[ty[j]].x) insert(j + n, ty[j]);

            t[j] = mp((ll) p[j].x, j);
            t[j + n] = mp((ll) p[j].x + len[i] + 1, j + n);
        }
        chkmin(ans, (ll) len[i] + calc());
    }
    printf("%lld\n", ans);
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
