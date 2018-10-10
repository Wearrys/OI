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
const double PI = acos(-1.0);

int n;
ll ans;
pii p[N + 5];

double ang(int x, int y) {
    double res = atan2(p[y].snd - p[x].snd, p[y].fst - p[x].fst);
    return res <= 0 ? res + PI : res;
}

ll calc(ll x) { return x * (x - 1) / 2; }

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    for(int i = 1; i <= n; ++i) read(p[i].fst), read(p[i].snd);
    for(int i = 1; i <= n; ++i) {
        vector<pair<double, int> > vec;
        for(int j = 1; j <= n; ++j) if(j != i) {
            vec.pb(mp(ang(i, j), j));
        }
        std::sort(vec.begin(), vec.end());

        int cnt[2] = {0, 0};
        static bool t[N + 5];

        for(int j = 1; j <= n; ++j) if(j != i) {
            if(p[j].snd < p[i].snd || (p[j].snd == p[i].snd && p[j].fst > p[i].fst)) {
                ++ cnt[t[j] = 1];
            } else {
                ++ cnt[t[j] = 0];
            }
        }
        for(int j = 0; j < (int) vec.size(); ++j) {
            -- cnt[t[vec[j].snd]];
            ans += calc(cnt[0]) * calc(cnt[1]);
            ++ cnt[t[vec[j].snd] ^ 1];
        }
    }
    printf("%lld\n", ans / 2);

    return 0;
}
