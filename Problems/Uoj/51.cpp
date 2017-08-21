#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb push_back
#define REP(i, a, b)  for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i=(a-1), i##end = (b); i >=i##end; --i)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const int oo = 0x3f3f3f3f;
const int maxn = 100000 + 10;

template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int val[maxn][32];
bool can[maxn][32];

int n, m;
void init() {
    int x = int(sqrt(n + 0.5));

    for(int i = 1; i <= 31; ++i) can[x+1][i] = 1;
    for(int i = x; i > 1; --i) {
        int j;
        val[i][1] = i;

        for(j = 2; ; ++j) { 
            val[i][j] = val[i][j-1] * i; 
            if(1LL * val[i][j] * i > n) { 
                for(int k = j+1; k <= 31; ++k) can[i][k] = 1;
                break; 
            }
        }
        for(; j >= 1; --j) {
            can[i][j] = (can[i+1][j] && can[i][j+1]) ? 0 : 1; 
        }
    }
}

int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    n = read<int>();
    m = read<int>();

    init();

    while(m--) { 
        int a, b;
        a = read<int>(), b = read<int>();
        if(1LL * a * a > n) {
            puts((n - a) & 1 ? "Yes" : "No");
            continue;
        }
        puts(can[a][b] ? "Yes" : "No"); 
    }

    return 0;
}
