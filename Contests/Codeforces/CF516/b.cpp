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

const int N = 2000;

int n, m, r, c, L, R;
int dis[N + 5][N + 5];
char st[N + 5][N + 5];

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(m);
    read(r), read(c); -- r, -- c;
    read(L), read(R);
    for(int i = 0; i < n; ++i) scanf("%s", st[i]);

    std::deque<pii> q;

    q.push_back(mp(r, c));
    memset(dis, oo, sizeof dis);
    dis[r][c] = 0;
    
    while(!q.empty()) {
        int x = q.front().fst, y = q.front().snd; 
        q.pop_front();

        for(int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m || st[nx][ny] == '*') continue;

            if(chkmin(dis[nx][ny], dis[x][y] + (i == 0))) {
                if(i != 0 && !q.empty()) {
                    q.push_front(mp(nx, ny));
                } else {
                    q.push_back(mp(nx, ny));
                }
            }
        }
    }

    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) if(st[i][j] != '*') {
            if(dis[i][j] <= L && (dis[i][j] - c + j) <= R) {
                ++ cnt;
            }
        }
    }
    printf("%d\n", cnt);

    return 0;
}
