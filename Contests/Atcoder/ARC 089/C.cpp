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
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

const int N = 300;

int A, B;
int d[N + 5][N + 5], f[N + 5][N + 5];

int n = 202, m;
struct edge { int u, v, w; } e[N * N + 5];

bool chk() {
    for(int x = 1; x <= A; ++ x) 
        for(int y = 1; y <= B; ++ y) {
            int mn = oo;
            for(int a = 0; a <= 100; ++ a) 
                for(int b = 0; b <= 100; ++ b) if(f[a][b] >= 0) 
                    chkmin(mn, f[a][b] + a*x + b*y);

            if(mn != d[x][y]) return false;
        }
    return true;
}
int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif 

    read(A), read(B);
    for(int i = 1; i <= A; ++i) 
        for(int j = 1; j <= B; ++j) read(d[i][j]);

    memset(f, ~oo, sizeof f);
    for(int a = 0; a <= 100; ++ a) 
        for(int b = 0; b <= 100; ++ b) {
            for(int x = 1; x <= A; ++ x) 
                for(int y = 1; y <= B; ++y) {
                    chkmax(f[a][b], d[x][y] - a * x - b * y);
                }

            // if(f[a][b] >= 0) debug("%d %d %d \n", a, b, f[a][b]);
        }

    if(!chk()) return !puts("Impossible");

    puts("Possible");

    for(int a = 0; a <= 100; ++ a) 
        for(int b = 0; b <= 100; ++ b) {
            if(f[a][b] >= 0) e[++ m] = (edge) { a + 1, n - b, f[a][b] };
        }
    for(int a = 2; a <= 101; ++ a) e[++ m] = (edge) { a-1, a, -1 };
    for(int b = n-99; b<= n; ++ b) e[++ m] = (edge) { b-1, b, -2 };

    printf("%d %d\n", n, m);
    for(int i = 1; i <= m; ++i) {
        printf("%d %d ", e[i].u, e[i].v);

        if(e[i].w >= 0) printf("%d\n", e[i].w);
        else {
            puts(e[i].w == -1 ? "X" : "Y");
        }
    }
    printf("%d %d\n", 1, n);

    return 0;
}
