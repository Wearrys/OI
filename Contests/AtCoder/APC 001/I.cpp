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

const int P = 100;
const int N = 1000000;
const int mo = 1e9 + 7;

const int dx[] = { -1, 1, 0, 0 };
const int dy[] = { 0, 0, -1, 1 };

int n, ans;
int cx[N + 5], cy[N + 5];
int ix[N + 5], iy[N + 5];
int sx[N + 5], sy[N + 5], totX, totY;

inline int size(int x, int y) {
    return 1ll * sx[x] * sy[y] % mo;
}

int solve(int *cnt, int *id, int *s, int R, int C) {
    int l = R - cnt[0], r = (1ll * R * C - n - l) % mo;

    ++ s[0];
    for(int i = 1; i < C; ++i) {
        id[i] = id[i-1];

        if(!cnt[i] && !cnt[i-1]) {
            ans = (ans + 1ll * l * r) % mo;
        } else {
            ++ id[i];
        }
        ++ s[id[i]];
        l = (l + R - cnt[i]) % mo;
        r = (r + cnt[i] - R) % mo;
    }
    return id[C - 1] + 1;
}

int r, c;
int dis[P + 5][P + 5];
bool vis[P + 5][P + 5];
int x[P + 5], y[P + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(r), read(c), read(n);
    for(int i = 0; i < n; ++i) {
        read(x[i]), read(y[i]);
        ++ cx[x[i]], ++ cy[y[i]];
    }

    totY = solve(cy, iy, sy, r, c);
    totX = solve(cx, ix, sx, c, r);

    ans = ans * 2 % mo;
    for(int i = 0; i < n; ++i) vis[ix[x[i]]][iy[y[i]]] = true;
    for(int i = 0; i < totX; ++i) 
        for(int j = 0; j < totY; ++j) if(!vis[i][j]) {
            std::queue<pii> q;
            memset(dis, 0xff, sizeof dis);

            dis[i][j] = 0;
            q.push(mp(i, j));

            while(!q.empty()) {
                pii cur = q.front(); q.pop();

                ans = (ans + 1ll * dis[cur.fst][cur.snd] * size(cur.fst, cur.snd) % mo * size(i, j)) % mo;

                for(int d = 0; d < 4; ++ d) {
                    pii nxt = mp(cur.fst + dx[d], cur.snd + dy[d]);

                    if(nxt.fst >= 0 && nxt.fst < totX &&!~dis[nxt.fst][nxt.snd]
                    && nxt.snd >= 0 && nxt.snd < totY && !vis[nxt.fst][nxt.snd]) {
                        dis[nxt.fst][nxt.snd] = dis[cur.fst][cur.snd] + 1;
                        q.push(nxt);
                    }
                }
            }
        }

    printf("%lld\n", 1ll * ans * (mo + 1) / 2 % mo);

    return 0;
}
