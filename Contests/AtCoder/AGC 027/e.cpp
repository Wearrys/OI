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

const int N = 200000;
const int mo = 1e9 + 7;

int n;
char st[N + 5];
int f[N + 5], lst[3];

bool chk() {
    for(int i = 1; i < n; ++i) {
        if(st[i] == st[i + 1]) return false;
    }
    return true;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%s", st + 1);
    n = strlen(st + 1);

    if(chk()) return !puts("1");

    f[0] = 1;
    lst[0] = 0;
    lst[1] = lst[2] = -1;

    int c = 0, all = 0;
    for(int i = 1; i <= n; ++i) all = (all + st[i] - 'a' + 1) % 3;
    for(int i = 1; i <= n; ++i) {
        c = (c + st[i] - 'a' + 1) % 3;
        for(int j = 1; j < 3; ++j) if(lst[(c-j+3)%3] >= 0) {
            f[i] = (f[i] + f[lst[(c-j+3)%3]]) % mo;
        }
        lst[c] = i;

        if(c == 0 && i < n) { f[i] = (f[i] + 1) % mo; }
    }
    printf("%d\n", f[n]);

    return 0;
}
