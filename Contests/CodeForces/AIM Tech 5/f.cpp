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

int n, all;
std::map <pii, int> cnt; 
std::map <ll, std::set<pii>> mp;

pii unit(int x, int y) {
    int r = std::__gcd(x, y);
    return mp(x / r, y / r);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    
    read(n);
    for(int i = 1; i <= n; ++i) {
        static int op, x, y;
        read(op), read(x), read(y);

        if(op == 1) {
            ++ all;
            ll dis = 1ll*x*x + 1ll*y*y;

            cnt[unit(x, y)] ++;
            for(auto v : mp[dis]) {
                cnt[unit(x + v.fst, y + v.snd)] += 2;
            }
            mp[dis].insert(mp(x, y));
        } else if(op == 2) {
            -- all;
            ll dis = 1ll*x*x + 1ll*y*y;

            cnt[unit(x, y)] --;
            mp[dis].erase(mp(x, y));
            for(auto v : mp[dis]) {
                cnt[unit(x + v.fst, y + v.snd)] -= 2;
            }
        } else {
            printf("%d\n", all - cnt[unit(x, y)]);
        }
    }

    return 0;
}
