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

int n, m, a, b;
int mark[N + 5][N + 5];

char idx(int x) {
    if(x == 0) return '.';
    if(x == 1) return '<';
    if(x == 2) return '>';
    if(x == 3) return '^';
    if(x == 4) return 'v';
    return 'X';
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(m), read(a), read(b);

    if(n & 1) {
        for (int i = 1; i < m; i += 2) {
            if(!mark[n][i] && !mark[n][i+1] && a) 
                mark[n][i] = 1, mark[n][i+1] = 2, -- a;
        }
    }

    if(m & 1) {
        for (int i = 1; i < n; i += 2) {
            if(!mark[i][m] && !mark[i+1][m] && b) 
                mark[i][m] = 3, mark[i+1][m] = 4, -- b;
        }
    }

    for (int i = 1; i < n; i += 2) 
        for (int j = 1; j < m; j += 2) {

            if(i == n - 2 && j == m - 2 && a == 1 && b == 1) {
                mark[i][j] = 1, mark[i][j+1] = 2, mark[i][j+2] = 3;
                mark[i+1][j] = 3, mark[i+1][j+1] = 0, mark[i+1][j+2] = 4;
                mark[i+2][j] = 4, mark[i+2][j+1] = 1, mark[i+2][j+2] = 2;

                a = 0, b = 0;
            } else if(a >= 2 || (a == 1 && (!b || (b == 1 && (i != n-2 || j != m-2))))) {
                if(a) mark[i][j] = 1, mark[i][j+1] = 2, -- a;
                if(a) mark[i+1][j] = 1, mark[i+1][j+1] = 2, -- a;
            } else if(b >= 2 || (b == 1 && (!a || (a == 1 && (i != n-2 || j != m-2))))) {
                if(b) mark[i][j] = 3, mark[i+1][j] = 4, -- b;
                if(b) mark[i][j+1] = 3, mark[i+1][j+1] = 4, -- b;
            }
        }

    if(a || b) return !puts("NO");

    puts("YES");
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            printf("%c", idx(mark[i][j])); 
        }
        puts("");
    }

    return 0;
}
