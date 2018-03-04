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

const int N = 50;

bool flag[N + 5][N + 5];
char grid[N + 5][N + 5];

int n, m, sx, sy, tx, ty;

inline pii get_nxt(int x, int y, char c) {
    if(c == 'w') return mp(x - 1, y);
    if(c == 's') return mp(x + 1, y);
    if(c == 'd') return mp(x, y + 1);
    return mp(x, y - 1);
}

bool vis[N + 5][N + 5];
void outp() {
    printf("%d %d %d %d %d %d\n", n, m, sx, sy, tx, ty);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) printf("%c", grid[i][j]);
        printf("\n");
    }
}

void get_path(int x, int y) {
    if(vis[x][y]) return;
    if(x < 0 || x > n || y < 0 || y > m) return;
    if(x == tx && y == ty) {outp(); exit(0);}

    vis[x][y] = true;

    pii temp;
    if(grid[x][y] != '.') {
        temp = get_nxt(x, y, grid[x][y]);
        get_path(temp.fst, temp.snd);
    } else {
        temp = get_nxt(x, y, grid[x][y] = 'w');
        get_path(temp.fst, temp.snd);

        temp = get_nxt(x, y, grid[x][y] = 'a');
        get_path(temp.fst, temp.snd);

        temp = get_nxt(x, y, grid[x][y] = 's');
        get_path(temp.fst, temp.snd);

        temp = get_nxt(x, y, grid[x][y] = 'd');
        get_path(temp.fst, temp.snd);
    }

    vis[x][y] = false;
}

int main() {
    freopen("6.txt", "r", stdin);
    freopen("6.out", "w", stdout);

    read(n), read(m), read(sx), read(sy), read(tx), read(ty);

    for(int i = 1; i <= n; ++i) {
        scanf("%s", grid[i] + 1);
    }
    
    get_path(sx, sy); 

    return 0;
}
