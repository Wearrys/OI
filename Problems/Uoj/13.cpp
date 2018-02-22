#include <bits/stdc++.h>
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
map<string, int> G[N + 5];
pair<string, int> fa[N + 5];
char st0[N + 5], st1[N + 5];

int cnt;
int insert(char *s, int ty) {
    int u = 0, cur = 1;
    int len = strlen(s);

    string tmp;
    while(cur < len) {

        tmp = "";
        for(; s[cur] != '/' && cur < len; cur ++) {
            tmp += s[cur];
        }

        if(cur == len && ty >= 0) {
            G[u][tmp] = ty;
            break;
        }

        if(G[u].find(tmp) == G[u].end()) {
            G[u][tmp] = ++ cnt;
            fa[G[u][tmp]] = make_pair(tmp, u);
        }

        u = G[u][tmp];
        ++ cur;
    }
    return u;
}

void out(int u) {
    if(!u) return;
    out(fa[u].snd);
    cout << '/' << fa[u].fst;
}

void print_ans(char *s) {
    int u = 0, cur = 1;
    int len = strlen(s);

    string tmp;
    while(cur < len) {

        tmp = "";
        for(; s[cur] != '/' && cur < len; cur++) {
            tmp += s[cur];
        }

        if(G[u].find(tmp) == G[u].end()) {
            out(u);
            cout << '/' << tmp;
            for(int j = cur; j < len; ++j) putchar(s[j]);
            puts("");
            return;
        }

        u = G[u][tmp];
        ++ cur;
    }
    out(u);
    if(!u) putchar('/');
    puts("");
}

int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif 

    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) {
        scanf("%s", st0); 
        scanf("%s", st1); 
        int x = insert(st1, -1);
        insert(st0, x);
    }
    for(int i = 1; i <= m; ++i) {
        scanf("%s", st0); print_ans(st0);
    }

    return 0;
}
