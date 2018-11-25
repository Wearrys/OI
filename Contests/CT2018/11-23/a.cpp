#include <bits/stdc++.h>
using namespace std;

const int N = 50000;
const int M = 500000;
const int oo = 0x3f3f3f3f;

int S, T;

namespace Dinic {

    struct edge {
        int to, nxt, cap;
    };

    edge e[M + 5];
    int st[N + 5], ecnt = 1;

    void clear() {
        ecnt = 1;
        memset(st, 0, sizeof st);
    }

    int addedge(int u, int v, int c) {
        e[++ ecnt] = (edge) { v, st[u], c }, st[u] = ecnt;
        e[++ ecnt] = (edge) { u, st[v], 0 }, st[v] = ecnt;
        return ecnt - 1;
    }

    int dis[N + 5], cur[N + 5];

    bool bfs() {
        static int que[N + 5];
        int head = 0, tail = 0;
        memset(dis, -1, sizeof dis);

        dis[S] = 0;
        que[tail ++] = S;

        while(head < tail) {
            int x = que[head ++];
            for(int i = st[x]; i; i = e[i].nxt) if(e[i].cap) {
                int y = e[i].to;
                if(dis[y] == -1) {
                    que[tail ++] = y;
                    dis[y] = dis[x] + 1;
                }
            }
        }
        return dis[T] >= 0;
    }

    int dfs(int x, int flow) {
        if(x == T || !flow) 
            return flow;

        int res = 0;
        for(int&i = cur[x]; i; i = e[i].nxt) {
            int y = e[i].to, aug;
            if(dis[y] == dis[x] + 1 && (aug = dfs(y, min(flow, e[i].cap)))) {
                res += aug;
                flow -= aug;
                e[i].cap -= aug;
                e[i ^ 1].cap += aug;
                if(!flow) break;
            }
        }
        return res;
    }

    int max_flow() {
        int ans = 0;
        while(bfs()) {
            memcpy(cur, st, sizeof st);
            ans += dfs(S, oo);
        }
        return ans;
    }
}

int n, m;
int a, b, c;
pair<int, int> e[N + 5];
int vis[N + 5], to[N + 5];
int idx[N + 5], idy[N + 5];
vector< vector<int> > path, ans;

void push(vector< vector<int> > &p, int x, int y, int s) {
    if(x == s) {
        p.push_back(vector<int> { x, y });
    } else {
        to[x] = y;
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d%d%d%d%d", &n, &m, &a, &b, &c);

    S = 2 * n + 1, T = S + 1;
    for(int i = 1; i <= n; ++i) {
        if(i == a) 
            Dinic::addedge(S, i + n, 3);
        else if(i == b) 
            Dinic::addedge(i, T, 3);
        else 
            Dinic::addedge(i, i + n, 1);
    } 

    for(int i = 1; i <= m; ++i) {
        static int x, y;
        scanf("%d%d", &x, &y);
        e[i] = make_pair(x, y);
        if(x != b && y != a) idx[i] = Dinic::addedge(x + n, y, 1); else idx[i] = -1;
        if(y != b && x != a) idy[i] = Dinic::addedge(y + n, x, 1); else idy[i] = -1;
    }

    assert(Dinic::max_flow() == 3);

    for(int i = 1; i <= m; ++i) {
        if(~idx[i] && Dinic::e[idx[i]].cap == 0) push(path, e[i].first, e[i].second, a); 
        if(~idy[i] && Dinic::e[idy[i]].cap == 0) push(path, e[i].second, e[i].first, a);
    }

    Dinic::clear();
    Dinic::addedge(S, c + n, 2);

    int cnt = 0;
    for(auto& p : path) {
        while(p.back() != b) p.push_back(to[p.back()]);

        int pos = 0;
        for(auto v : p) if(!vis[v]) {
            vis[v] = (++ pos) * 3 + cnt;
            Dinic::addedge(v, T, 1);
        }
        ++ cnt;
    }

    vector<int> res;

    if(vis[c]) {
        c = vis[c];
        for(auto v : path[c % 3]) res.push_back(v);
        for(int i = (int) path[(c + 1) % 3].size() - 2; i >= 0; --i) res.push_back(path[(c + 1) % 3][i]);
        printf("%d\n", (int) res.size() - 1);
        for(auto v : res) printf("%d ", v);
        return 0;
    } 

    for(int i = 1; i <= n; ++i) if(i != c && !vis[i]) Dinic::addedge(i, i + n, 1);
    for(int i = 1; i <= m; ++i) {
        int x = e[i].first, y = e[i].second;
        if(y != c) idx[i] = Dinic::addedge(x + n, y, 1); else idx[i] = -1;
        if(x != c) idy[i] = Dinic::addedge(y + n, x, 1); else idy[i] = -1;
    }

    if(Dinic::max_flow() != 2) {
        puts("-1");
    } else {
        memset(to, 0, sizeof to);
        for(int i = 1; i <= m; ++i) {
            if(~idx[i] && Dinic::e[idx[i]].cap == 0) push(ans, e[i].first, e[i].second, c); 
            if(~idy[i] && Dinic::e[idy[i]].cap == 0) push(ans, e[i].second, e[i].first, c);
        }
        for(auto& p : ans) while(!vis[p.back()] && to[p.back()]) p.push_back(to[p.back()]);

        int x = vis[ans[0].back()], y = vis[ans[1].back()];

        if(x % 3 == y % 3) {
            if(x > y) std::swap(ans[0], ans[1]);

            for(auto v : path[x % 3]) {
                if(v == ans[0].back()) break;
                res.push_back(v);
            }
            for(int i = (int) ans[0].size() - 1; i > 0; --i) res.push_back(ans[0][i]);
            for(int i = 0; i < (int) ans[1].size() - 1; ++i) res.push_back(ans[1][i]);
            for(int i = 0; i < (int) path[y % 3].size(); ++i) if(path[y % 3][i] == ans[1].back()) {
                for(int j = i; j < (int) path[y % 3].size(); ++j) {
                    res.push_back(path[y % 3][j]);
                } break;
            }
            for(int i = (int) path[(x + 1) % 3].size() - 2; i >= 0; --i) {
                res.push_back(path[(x + 1) % 3][i]);
            }
        } else {
            if(x > y) std::swap(ans[0], ans[1]), swap(x, y);

            for(auto v : path[x % 3]) {
                if(v == ans[0].back()) break;
                res.push_back(v);
            }
            for(int i = (int) ans[0].size() - 1; i > 0; --i) res.push_back(ans[0][i]);
            for(int i = 0; i < (int) ans[1].size() - 1; ++i) res.push_back(ans[1][i]);
            for(int i = 0; i < (int) path[y % 3].size(); ++i) if(path[y % 3][i] == ans[1].back()) {
                for(int j = i; j < (int) path[y % 3].size(); ++j) {
                    res.push_back(path[y % 3][j]);
                } break;
            }

            int z = ((3 - x - y) % 3 + 3) % 3;

            assert(z != x % 3 && z != y % 3);
            for(int i = (int) path[z].size() - 2; i >= 0; --i) {
                res.push_back(path[z][i]);
            }
        }

        printf("%d\n", (int) res.size() - 1);
        for(auto v : res) printf("%d ", v);
    }

    return 0;
}
