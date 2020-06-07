#include <bits/stdc++.h>
using namespace std;

const int N = 1000 + 10;
const int M = 1000000;
const int oo = 0x3f3f3f3f;

int n, m;
int d[N + 5];
int S, T, SS, TT;

struct edge {
    int to, nxt, cap, cost;
    edge() { }
    edge(int x, int y, int c, int w): to(x), nxt(y), cap(c), cost(w) {}
};

edge e[M];
int head[N + 5], ecnt = 1;

void addedge(int u, int v, int cap, int cost) {
    e[++ ecnt] = edge(v, head[u], cap, cost); head[u] = ecnt;
    e[++ ecnt] = edge(u, head[v], 0, - cost); head[v] = ecnt;
}

long long ans = 0;
void addedge(int u, int v, int low, int high, int cost) {
    d[u] += low;
    d[v] -= low;
    addedge(u, v, high - low, cost);

    ans += 1ll * low * cost;
}

bool inq[N + 5];
int cap[N + 5];
int pre[N + 5], dis[N + 5];

bool spfa() {

    queue<int> que;

    memset(dis, 0x3f, sizeof dis);

    //assert(dis[0] == oo);
    dis[SS] = 0;
    cap[SS] = oo;
    que.push(SS);

    while (!que.empty()) {
        int x = que.front(); que.pop(); 

        inq[x] = false;
        for (int i = head[x]; i; i = e[i].nxt) if (e[i].cap) {
            int y = e[i].to;
            if (dis[x] + e[i].cost < dis[y]) {
                pre[y] = i;
                cap[y] = min(cap[x], e[i].cap);
                dis[y] = dis[x] + e[i].cost;

                if (!inq[y]) {
                    que.push(y);
                    inq[y] = true;
                }
            }
        }
    }

    if (dis[TT] >= oo) return false;

    for (int i = TT; i != SS; i = e[pre[i] ^ 1].to) {
        e[pre[i] ^ 1].cap += cap[TT];
        e[pre[i]].cap -= cap[TT];
    }
    ans += 1ll * cap[TT] * dis[TT];

    return true;
}

void input() {
    static bool in[N + 5], out[N + 5];

    scanf("%d%d", &n, &m);
    S = 2 * n + 1, T = S + 1;
    SS = T + 1, TT = SS + 1;

    for (int i = 1; i <= m; ++i) {
        int x, y, c;
        scanf("%d%d%d", &x, &y, &c);
        out[x] = in[y] = true;
        addedge(x, y + n, 0, 1, c);
    }

    for (int i = 1; i <= n; ++i) {
        if (!in[i] || !out[i]) {
            puts("NIE");
            exit(0);
        }

        addedge(S, i, 1, n, 0);
        addedge(i + n, T, 1, n, 0);
    }

    addedge(T, S, 0, oo, 0);

    for (int i = 1; i <= T; ++i) if (d[i] != 0) {
        if (d[i] > 0) {
            addedge(i, TT, d[i], 0);
        } else {
            addedge(SS, i, -d[i], 0);
        }
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
#endif

    input();
    while (spfa());

    printf("%lld\n", ans);

    return 0;
}
