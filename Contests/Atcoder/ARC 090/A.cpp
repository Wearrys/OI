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
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

const int N = 1000;

int n, ans;
int a[2][N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif 

    read(n);
    for(int d = 0; d < 2; ++ d) {
        for(int i = 1; i <= n; ++i) {
            read(a[d][i]);
        }
    }

    for(int i = n; i >= 1; --i) a[1][i] += a[1][i+1];
    for(int i = 1; i <= n; ++i) a[0][i] += a[0][i-1], chkmax(ans, a[0][i] + a[1][i]);

    printf("%d\n", ans);

    return 0;
}
