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

const int mo = 1e9 + 7;

int n;
char st[25];
std::set <int> s;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int l = -oo, r = oo, a = 1, b = 1;

    s.insert(l), s.insert(r);

    read(n);
    for(int i = 1; i <= n; ++i) {
        int x;
        scanf("%s", st); read(x);

        if(st[1] == 'D') {
            s.insert(x);
            if(l < x && x < r) ++ a;
        } else {
            a = 1;
            if(l <= x && x <= r) {
                if(x != l && x != r) b = b * 2 % mo;
                std::set<int> :: iterator it = s.find(x);
                -- it; l = *it;
                ++ it; 
                ++ it; r = *it;
                s.erase(x);
            } else return puts("0"), 0;
        }
    }
    printf("%lld\n", (ll) a * b % mo);

    return 0;
}
