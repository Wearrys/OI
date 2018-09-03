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

int n;
const int N = 200000;

struct node {
    int x1, y1, x2, y2;
};

node t[N + 5];
std::multiset<int> s[4];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    for(int i = 1; i <= n; ++i) {
        s[0].insert(read(t[i].x1));
        s[1].insert(read(t[i].y1));
        s[2].insert(read(t[i].x2));
        s[3].insert(read(t[i].y2));
    }

    for(int i = 1; i <= n; ++i) {
        s[0].erase(s[0].find(t[i].x1));
        s[1].erase(s[1].find(t[i].y1));
        s[2].erase(s[2].find(t[i].x2));
        s[3].erase(s[3].find(t[i].y2));

        int l = (*s[0].rbegin()), r = (*s[2].begin());
        int d = (*s[1].rbegin()), u = (*s[3].begin());

        if(l <= r && d <= u) {
            printf("%d %d\n", l, d);
            break;
        }

        s[0].insert(t[i].x1);
        s[1].insert(t[i].y1);
        s[2].insert(t[i].x2);
        s[3].insert(t[i].y2);
    }

    return 0;
}
