#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back

template <typename T> inline bool chkmax(T& a, T b) { return a <= b ? a = b, 1 : 0; }
template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int maxn = 1e5 + 10;
const int oo = 0x3f3f3f3f;

template<typename T> inline T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

struct Deque {
    int q[maxn];
    int head, tail;
    inline void clear() { head = tail = 0; }
    inline int size() { return tail - head; }
    inline int front(int p) { return q[head + p]; }
    inline int end(int p) { return q[tail-1-p]; }
    inline void push(int x) { q[tail++] = x; }
}q1, q2;

int n, K, cur = 1;
int pre[maxn][210];
long long dp[2][maxn], a[maxn], s[maxn];

void out(int x, int dep) {
    if(dep > 1) 
        out(pre[x][dep], dep-1);
    if(x < n) printf("%d ", x);
}

inline double slope(int x, int y, bool t) {
    return s[y] == s[x] ? 1e18 : double(dp[t][y] - dp[t][x]) / (s[y] - s[x]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    n = read<int>(), K = read<int>();
    for(int i = 1; i <= n; ++i) s[i] = s[i-1] + (a[i] = read<int>());

    q1.push(0);
    for(int i = 1; i <= K+1; ++i) {
        q2.clear();

        for(int j = i; j <= n; j++) {
            while(q1.size() > 1 && q1.front(1) < j 
                                && slope(q1.front(0), q1.front(1), cur^1) > double(s[n]-s[j]))
                ++ q1.head;

            pre[j][i] = q1.front(0);
            dp[cur][j] = dp[cur^1][pre[j][i]]  + (s[j] - s[pre[j][i]]) * (s[n] - s[j]);

            while(q2.size() > 1 && slope(q2.end(1), q2.end(0), cur) <= slope(q2.end(0), j, cur))
                -- q2.tail;
            q2.push(j);
        }
        cur ^= 1;
        swap(q1, q2);
    }
    printf("%lld\n", dp[cur^1][n]); out(n, K+1);

    return 0;
}
