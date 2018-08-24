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

const int N = 100;

struct point {
    int x, y, id;

    bool operator < (const point& rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

int n, m;
int S[N + 5], T[N + 5];
point s[N + 5], t[N + 5];
vector<pair<pii, pii> > ans, res;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(m);
    for(int i = 1; i <= m; ++i) read(s[i].x), read(s[i].y), s[i].id = i;
    for(int i = 1; i <= m; ++i) read(t[i].x), read(t[i].y), t[i].id = i;

    std::sort(s + 1, s + m + 1);
    std::sort(t + 1, t + m + 1);

    while(true) {
        bool flag = false;
        for(int i = 1; i <= m; ++i) {
            if(s[i].y > i) flag = true, ans.pb(mp(mp(s[i].x, s[i].y), mp(s[i].x, s[i].y - 1))), -- s[i].y;
            if(t[i].y > i) flag = true, res.pb(mp(mp(t[i].x, t[i].y), mp(t[i].x, t[i].y - 1))), -- t[i].y;
        }
        for(int i = m; i >= 1; --i) {
            if(s[i].y < i) flag = true, ans.pb(mp(mp(s[i].x, s[i].y), mp(s[i].x, s[i].y + 1))), ++ s[i].y;
            if(t[i].y < i) flag = true, res.pb(mp(mp(t[i].x, t[i].y), mp(t[i].x, t[i].y + 1))), ++ t[i].y;
        }
        if(!flag) break;
    }

    for(int i = 1; i <= m; ++i) {
        while(s[i].x > s[i].id) ans.pb(mp(mp(s[i].x, s[i].y), mp(s[i].x - 1, s[i].y))), -- s[i].x;
        while(s[i].x < s[i].id) ans.pb(mp(mp(s[i].x, s[i].y), mp(s[i].x + 1, s[i].y))), ++ s[i].x;
        while(t[i].x > t[i].id) res.pb(mp(mp(t[i].x, t[i].y), mp(t[i].x - 1, t[i].y))), -- t[i].x;
        while(t[i].x < t[i].id) res.pb(mp(mp(t[i].x, t[i].y), mp(t[i].x + 1, t[i].y))), ++ t[i].x;

        S[s[i].x] = s[i].y;
        T[t[i].x] = t[i].y;
    }

    for(int i = 1; i <= m; ++i) {
        while(S[i] < T[i]) ans.pb(mp(mp(i, S[i]), mp(i, S[i] + 1))), ++ S[i];
        while(S[i] > T[i]) ans.pb(mp(mp(i, S[i]), mp(i, S[i] - 1))), -- S[i];
    }

    printf("%d\n", (int) (ans.size() + res.size()));

    std::reverse(res.begin(), res.end());
    for(auto& step : ans) printf("%d %d %d %d\n", step.fst.fst, step.fst.snd, step.snd.fst, step.snd.snd);
    for(auto& step : res) printf("%d %d %d %d\n", step.snd.fst, step.snd.snd, step.fst.fst, step.fst.snd);

    return 0;
}
