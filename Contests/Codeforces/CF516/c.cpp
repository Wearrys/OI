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
int showpoint(int x, int y) {
    static char st[100];
    printf("%d %d\n", x, y);
    fflush(stdout);

    scanf("%s", st);
    return st[0] == 'b' ? 1 : 0;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    int l = 1, r = (int) 1e9 - 1;
    int ty = showpoint(0, 1);

    for(int i = 1; i < n; ++i) {
        if(l <= r) {
            int mid = (l + r) >> 1;
            if(showpoint(mid, 1) == ty) 
                l = mid + 1;
            else 
                r = mid - 1;
        } else {
            assert(i == n - 1);
            if(showpoint(l - 1, 3) == ty) {
                printf("%d %d %d %d\n", l, 0, l - 1, 2);
            } else {
                printf("%d %d %d %d\n", l - 1, 0, l, 2);
            }
            return 0;
        }
    }
    printf("%d %d %d %d\n", l - 1, 0, l, 2);
    return 0;
}
