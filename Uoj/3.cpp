#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back
#define getchar getchar_unlocked

template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;
const int maxn = 2e5 + 10;

template<typename T> T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48;
	return n * f;
}

struct Edge {
    int u, v, a, b;    
    void input() {
        u = read<int>(), v = read<int>();
        a = read<int>(), b = read<int>();
    }
    bool operator < (const Edge& rhs) const {
        return a < rhs.a;
    }
}E[maxn];

int n, m;
namespace LCT {

#define TY(u) (c[fa[u]][1] == u) 
#define rt(u) (c[fa[u]][0] != u && c[fa[u]][1] != u)

    bool rev[maxn];
    pii mx[maxn];
    int fa[maxn], c[maxn][2];

    void push_up(int u) {
        mx[u] = u <= n ? pii(0, 0) : pii(E[u-n].b, u-n);

        chkmax(mx[u], mx[c[u][0]]);
        chkmax(mx[u], mx[c[u][1]]);
    }
    void push_down(int u) {
        if(rev[u]) {
            rev[u] = 0;
            swap(c[u][0], c[u][1]);

            rev[c[u][0]] ^= 1;
            rev[c[u][1]] ^= 1;
        }
    }
    void rotate(int u) {
        int v = fa[u], w = fa[v];
        bool t = (c[v][1] == u);

        if(!rt(v)) c[w][c[w][1] == v] = u;
        c[v][t] = c[u][t^1]; fa[c[u][t^1]] = v;
        c[u][t^1] = v; fa[v] = u; fa[u] = w;

        push_up(v);
    }
    void Push(int u) {
        if(!rt(u)) Push(fa[u]);
        push_down(u);
    }
    void splay(int u) {
        Push(u);

        while(!rt(u)) {
            if(!rt(fa[u]))
                rotate(TY(u) == TY(fa[u]) ? fa[u] : u); 
            rotate(u);
        }
        push_up(u);
    }
    int access(int u) {
        int v;
        for(v = 0; u; u = fa[v = u]) {
            splay(u);
            c[u][1] = v;
            push_up(u);
        }
        return v;
    }
    void set_rt(int u) { rev[access(u)] ^= 1; splay(u); }
    void link(int u, int v) { set_rt(u); fa[u] = v; access(u); }
    void cut(int u, int v) { 
        set_rt(u); 
        access(v), splay(v); 
        c[v][0] = fa[c[v][0]] = 0; 
        push_up(v); 
    }
    int find_rt(int u) { 
        access(u); splay(u);
        while(c[u][0]) u = c[u][0]; 
        return u; 
    }
    pii get_mx(int u, int v) { set_rt(u); access(v); splay(v); return mx[v]; }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    n = read<int>(); m = read<int>();
    for(int i = 1; i <= m; i++) { E[i].input(); }

    sort(E+1, E+m+1);

    int ans = oo;
    for(int i = 1; i <= m; i++) {
        if(E[i].a >= ans) break;

        int u = E[i].u, v = E[i].v;

        if(LCT::find_rt(u) ^ LCT::find_rt(v)) {
            LCT::link(u, i+n);
            LCT::link(i+n, v);
        }else {
            pii tmp = LCT::get_mx(u, v); 

            if(E[i].b < tmp.fst) {

                LCT::cut(E[tmp.snd].u, tmp.snd+n);
                LCT::cut(tmp.snd+n, E[tmp.snd].v);

                LCT::link(u, i+n);
                LCT::link(i+n, v);
            }
        }
        if(LCT::find_rt(1) == LCT::find_rt(n)) {
            chkmin(ans, E[i].a + LCT::get_mx(1,n).fst);
        }

    }
    printf("%d\n", ans == oo ? -1 : ans);
    return 0;
}
