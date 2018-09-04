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

int n;
ll a[N + 5], b[N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    bool flag = true;
    read(n);
    for(int i = 1; i <= n; ++i) read(a[i]), flag &= (a[i] == 0);

    if(flag) {
        puts("YES");
        for(int i = 1; i <= n; ++i) {
            printf("%d ", 1);
        }
    } else {

#define nxt(i) ((i == n) ? 1 : i + 1)
#define lst(i) ((i == 1) ? n : i - 1)

        int u = -1;
        for(int i = 1; i <= n; ++i) {
            if(a[i] < a[nxt(i)]) {
                u = nxt(i);
                break;
            }
        }

        if(u == -1) puts("NO");
        else {
            puts("YES");
            b[u] = a[u]; 
            for(int i = lst(u); i != u; i = lst(i)) {
                ll lim = a[lst(i)];
                b[i] = ((lim - a[i]) / b[nxt(i)] + 1) * b[nxt(i)] + a[i];
            }
            for(int i = 1; i <= n; ++i) printf("%lld ", b[i]);
        }
    }

    return 0;
}
