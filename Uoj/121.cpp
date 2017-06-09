#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back
#define getchar getchar_unlocked

template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;
const int maxn = 1e5 + 10;

template<typename T> inline T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48;
	return n * f;
}

int n, d, K;
int x[maxn][110];
int tmp[maxn], line[maxn];

inline void search(int i) {
    int ans;
    for(int j = 1; j <= n; ++j) if(i ^ j) {
        ans = 0;
        for(int k = 1; k <= d; ++k) 
            ans += x[i][k] * x[j][k];
        if(ans % K == 0) {
            printf("%d %d\n", min(i, j), max(i, j));
            return;
        }
    }
}

inline void BF() {
    int ans;
    for(int i = 1; i <= n; ++i)
        for(int j = i+1; j <= n; ++j) {
            ans = 0;
            for(int k = 1; k <= d; ++k) ans += x[i][k] * x[j][k];
            ans %= K;
            if(ans == 0) {
                printf("%d %d\n", i, j);
                return;
            }
        }
    puts("-1 -1");
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    scanf("%d%d%d", &n, &d, &K);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= d; ++j) 
            x[i][j] = read<int>() % K;

    if(n <= 1000) return BF(), 0;
        
    int t, p;
    if(K == 2) {
        for(int i = 1; i <= d; ++i) 
            for(int j = 1; j <= n; ++j) tmp[i] ^= x[j][i];

        for(int i = 1; i <= n; ++i) 
            for(int j = 1; j <= d; ++j) line[i] ^= x[i][j] & x[i][j];

        for(int i = 1; i <= n; ++i) {
            t = 0; for(int j = 1; j <= d; ++j) t ^= x[i][j] & tmp[j];

            if(t != (((n-1) & 1) ^ line[i])) return search(i), 0;
        }
    }else {
        for(int i = 1; i <= d; ++i) 
            for(int j = 1; j <= d; ++j) {
                p = (i-1) * d + j;
                for(int k = 1; k <= n; ++k) tmp[p] += x[k][i] * x[k][j];
                tmp[p] %= K;
            }

        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= d; ++j)
                line[i] += x[i][j] * x[i][j];
            (line[i] *= line[i]) %= K;
        }

        for(int i = 1; i <= n; ++i) {
            t = 0;
            for(int j = 1; j <= d; ++j)
                for(int k = 1; k <= d; ++k) {
                    p = (j-1) * d + k;
                    t += x[i][j] * x[i][k] * tmp[p];
                }
            t %= K;
            if(t != (n-1 + line[i]) % K)
                return search(i), 0;
        }
    }
    puts("-1 -1");
    return 0;
}
