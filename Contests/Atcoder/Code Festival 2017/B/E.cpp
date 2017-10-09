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
const int maxn = 2000 + 5;
const int mod = 1e9 + 7;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int A, B;
LL C[maxn][maxn], D[maxn][maxn];

void init() {
    for(int i = 0; i < maxn; ++i) {
        C[i][0] = C[i][i] = 1;
        for(int j = 1; j < i; ++j) 
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
    }

    for(int i = 0; i < maxn; ++i) {
        D[i][0] = C[i][0];
        for(int j = 1; j < maxn; ++j)
            D[i][j] = (D[i][j-1] + C[i][j]) % mod;
    }
}

int main() {
#ifdef Wearry
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    init();
    cin >> A >> B;

    LL ans = 0;
    for(int i = 0; i <= A; ++i) {
        LL res = 0;
        for(int j = 1; j <= A - i; ++j) {
            res = (res + C[B - 1][j] * D[j - 1][A - i - j]) % mod;
        }
        ans = (ans + (i + 1) * res) % mod;
    }
    ans = (ans + A + 1) % mod;
    printf("%lld\n", ans);

    return 0;
}
