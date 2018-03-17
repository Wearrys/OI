#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp> //__gnu_pbds::priority_queue
 
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
 
const int N = 400;
const int mo = 1e9 + 7;
const int oo = 0x3f3f3f3f;
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

int G[N + 5][N + 5];
void insert(int x, int y) {
    //debug("%d %d\n", x, y);
    ++ G[x][x];
    -- G[y][x];
}

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1) 
            res = 1ll * res * x % mo;
        x = 1ll * x * x % mo;
    }
    return res;
}

int Gauss(int n) {
    bool rev = 0;
    for(int i = 1; i < n; ++i) {

        for(int j = i; j < n; ++j) {
            if(G[j][i]) {
                rev ^= (i != j);
                std::swap(G[j], G[i]);
                break;
            }
        }

        if(!G[i][i]) return 0;
        for(int j = i+1; j < n; ++j) if(G[j][i]) {
            int p = 1ll * G[j][i] * fpm(G[i][i], mo - 2) % mo;
            for(int k = i; k < n; ++k) {
                G[j][k] = (G[j][k] - 1ll * p * G[i][k]) % mo;
            }
        }
    }

    int res = 1;
    for(int i = 1; i < n; ++i) res = 1ll * res * G[i][i] % mo;
    return rev ? mo - res : res;
}

pii d[256];
int T, n, m;
char grid[N + 5][N + 5];

int fa[N*N + 5], id[N*N + 5];
int findset(int x) {
    return x == fa[x] ? x : fa[x] = findset(fa[x]);
}

const int dx[] = { 0, 0, 1, -1 };
const int dy[] = { 1, -1, 0, 0 };

int main() {
#ifdef Wearry
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif 

    d['L'] = mp(0, -1); 
    d['U'] = mp(-1, 0);
    d['D'] = mp(1, 0);
    d['R'] = mp(0, 1); 

    read(T);
    while(T--) {

        read(n), read(m);
        for(int i = 0; i <= n*m; ++i) fa[i] = i, id[i] = -1;

        bool flag = false;
        for(int i = 0; i < n; ++i) { scanf("%s", grid[i]); }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                int c = grid[i][j];
                int x = i + d[c].fst, y = j + d[c].snd;

                if(c != '.') { 
                    int u = i*m + j;
                    int v = (x >= 0 && x < n && y >= 0 && y < m) ? x*m + y : n*m;

                    if(findset(u) == findset(v)) {
                        flag = true;
                    }
                    fa[findset(u)] = findset(v);
                }
            }
        }
        if(flag) { puts("0"); continue; }

        int totId = 0;

        id[n*m] = totId ++;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                int x = findset(i*m+j);
                if(id[x] == -1) 
                    id[x] = totId ++;
                id[i*m+j] = id[x];
            }
        }
        if(totId >= N) for(;;);
        //debug("%d\n", totId);

        memset(G, 0, sizeof G);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(grid[i][j] == '.') {
                    for(int x = 0; x < 4; ++x) {
                        int nx = i + dx[x], ny = j + dy[x];

                        insert(id[i*m+j], (nx >= 0 && nx < n && ny >= 0 && ny < m) ? id[nx*m+ny] : id[n*m]);
                    }
                }
            }
        }

        printf("%d\n", (Gauss(totId) % mo + mo) % mo);
    }

    return 0;
}
