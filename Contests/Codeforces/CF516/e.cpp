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

int n;
bool vis[N + 5];

int lst[N + 5];
int Lst[N + 5];
int ans[N + 5][N + 5];
int a[N + 5], from[N + 5];

void chk() {
    for(int i = 1; i <= n; ++i) if(a[i] != i) { return; }
    printf("%d\n", n);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            putchar('.');
        }
        puts("");
    }
    exit(0);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", a + i), from[a[i]] = i;

    chk();

    int cur = 0;
    for(int i = 1; i <= n; ++i) if(a[i] != i) { cur = i; break; }
    for(int i = from[cur]; i != cur; i = from[i]) vis[i] = true;

    int c = n, dir;

    for(int i = cur + 1; i <= n; ++i) if(a[i] != i && !vis[i]) {
        dir = 1;
        vis[i] = true;
        ans[c][i] = ans[c][cur] = 1;

        for(int j = from[i]; j != i; j = from[j]) {
            
            vis[j] = true;
            if(a[j] < j) {
                c -= (dir == 2);
                dir = ans[c][a[j]] = ans[c][j] = 1;
            } else {
                c -= (dir == 1);
                dir = ans[c][a[j]] = ans[c][j] = 2;
            }
        }
        -- c;
        ans[c][cur] = ans[c][a[i]] = 2;
        -- c;
    }

    dir = 1;
    for(int i = from[cur]; i != cur; i = from[i]) {
        if(a[i] < i) {
            c -= (dir == 2);
            dir = ans[c][a[i]] = ans[c][i] = 1;
        } else {
            c -= (dir == 1);
            dir = ans[c][a[i]] = ans[c][i] = 2;
        }
    }

    printf("%d\n", n - 1);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            printf("%c", ans[i][j] == 0 ? '.' : (ans[i][j] == 1 ? '\\' : '/'));
        }
        puts("");
    }

    return 0;
}
