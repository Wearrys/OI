#include <bits/stdc++.h>
#include <tr1/unordered_map>
using namespace std;
 
typedef long long LL;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb push_back
#define REP(i, a, b)  for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i=(a-1), i##end = (b); i >=i##end; --i)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const int N = 500000;
const int oo = 0x3f3f3f3f;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int n, m;
struct Op {
    int ty;
    int u, v;
} op[N + 5];

int fa[N + 5], rk[N + 5];
int findset(int u) {
    return (u == fa[u]) ? u : findset(fa[u]);
}

int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif 

    n = read<int>();
    m = read<int>();
    for(int i = 1; i <= m; ++i) {
        int u, v;
        char st[10]; scanf("%s", st);

        if(st[0] == 'A') {
            u = read<int>();
            v = read<int>();
            op[i] = (Op) { 0, u, v };
        }else if(st[0] == 'D') {
            u = read<int>();
            op[i] = (Op) { 1, u, 0 };
        }else {
            if(op[i-1].ty == 0) {
                op[i] = (Op) { 1, 1, 0 };
            }else {
                op[i] = (Op) { 2, 0, 0 };
            }
        }
    }

    LL ans = 0;
    pii stk[N + 5];
    int edges = 0, top = 0, none = 0;

    for(int i = 1; i <= n; ++ i) fa[i] = i, rk[i] = 1;
    for(int i = 1; i <= m; ++ i) {
        if(op[i].ty == 0) {
            int x = findset(op[i].u), y = findset(op[i].v);

            //cerr << x << ' ' << y << endl;
            if(x == y) stk[top ++] = pii(-1, -1), ++ none;
            else {
                none = 0;
                ++ edges;
                ans += i;

                if(rk[x] > rk[y]) swap(x, y);

                fa[x] = y;
                rk[y] += rk[x];
                stk[top ++] = pii(x, i);
            }
        }else if(op[i].ty == 1) {
            if(op[i+1].ty == 2) {
                printf("%lld\n", (op[i].u <= none && edges == n-1) ? ans : 0);
                continue;
            }else {
                for(int ti = op[i].u; ti--; ) {
                    if(stk[-- top].fst > 0) {
                        int x = stk[top].fst, w = stk[top].snd; 

                        rk[fa[x]] -= rk[x]; fa[x] = x;

                        -- edges;
                        ans -= w;

                    }else -- none;
                }
            }
        }
        printf("%lld\n", (edges == n - 1) ? ans : 0);
    }

    return 0;
}
