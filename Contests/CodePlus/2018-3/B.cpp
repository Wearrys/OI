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

const int N = 100000;

int n, T;
struct area {
    int x0, y0, x1, y1;

    int s(bool a, bool b) {
        return (a ? x1 : x0) + (b ? y1 : y0);
    }
};

int cnt[2];
area p[2][N + 5];
pii s[2][2][2][2][N + 5];

std::map<int, bool> mp;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(T);
    while (T--) {
        cnt[0] = cnt[1] = 0;

        read(n);
        bool tag = true;
        for(int i = 1; i <= n; ++i) {
            static int x, y, w, h, d;
            read(x), read(y), read(w), read(h); read(d);

            ++ cnt[d];
            p[d][cnt[d]].x0 = x; p[d][cnt[d]].x1 = x + w;
            p[d][cnt[d]].y0 = y; p[d][cnt[d]].y1 = y + h;

            tag &= (w == 1 && h == 1);
        }

        int pos;
        bool flag = false;

        for(int a = 0; a < 2; ++a) for(int b = 0; b < 2; ++b) if((a == 1 && b == 1) || (a == 0 && b == 1))
        for(int c = 0; c < 2; ++c) for(int d = 0; d < 2; ++d) {
            for(int i = 1; i <= cnt[0]; ++i) s[a][b][c][d][i] = mp(p[0][i].s(a, b), p[0][i].s(c, d));
            std::sort(s[a][b][c][d] + 1, s[a][b][c][d] + cnt[0] + 1);
            for(int i = cnt[0]-1; i >= 1; --i) chkmin(s[a][b][c][d][i].snd, s[a][b][c][d][i + 1].snd);
        }

        for(int i = 1; i <= cnt[1]; ++i) {
            pos = std::lower_bound(s[1][1][1][0] + 1, s[1][1][1][0] + cnt[0] + 1, mp(p[1][i].s(0, 0) + 1, INT_MIN)) - s[1][1][1][0];
            if(pos <= cnt[0] && s[1][1][1][0][pos].snd <= p[1][i].s(0, 1)) flag = true;
            pos = std::lower_bound(s[0][1][0][0] + 1, s[0][1][0][0] + cnt[0] + 1, mp(p[1][i].s(1, 0), INT_MIN)) - s[0][1][0][0];
            if(pos <= cnt[0] && s[0][1][0][0][pos].snd + 1 <= p[1][i].s(1, 1)) flag = true;
            if(flag) break;
        }

        for(int a = 0; a < 2; ++a) for(int b = 0; b < 2; ++b) if((a == 1 && b == 1) || (a == 1 && b == 0))
        for(int c = 0; c < 2; ++c) for(int d = 0; d < 2; ++d) {
            for(int i = 1; i <= cnt[1]; ++i) s[a][b][c][d][i] = mp(p[1][i].s(a, b), p[1][i].s(c, d));
            std::sort(s[a][b][c][d] + 1, s[a][b][c][d] + cnt[1] + 1);
            for(int i = cnt[1]-1; i >= 1; --i) chkmin(s[a][b][c][d][i].snd, s[a][b][c][d][i + 1].snd);
        }

        for(int i = 1; i <= cnt[0]; ++i) {
            pos = std::lower_bound(s[1][1][0][1] + 1, s[1][1][0][1] + cnt[1] + 1, mp(p[0][i].s(0, 0) + 1, INT_MIN)) - s[1][1][0][1];
            if(pos <= cnt[1] && s[1][1][0][1][pos].snd <= p[0][i].s(1, 0)) flag = true;
            pos = std::lower_bound(s[1][0][0][0] + 1, s[1][0][0][0] + cnt[1] + 1, mp(p[0][i].s(0, 1), INT_MIN)) - s[1][0][0][0];
            if(pos <= cnt[1] && s[1][0][0][0][pos].snd + 1 <= p[0][i].s(1, 1)) flag = true;
            if(flag) break;
        }

        printf("%d\n", 1 + flag);
    }

    return 0;
}
