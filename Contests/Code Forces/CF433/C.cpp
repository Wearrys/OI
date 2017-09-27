#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb push_back
#define eb emplace_back
#define REP(i, a, b)  for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i=(a-1), i##end = (b); i >=i##end; --i)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const int oo = 0x3f3f3f3f;
const int maxn = 300000 + 5;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int n, k;
int a[maxn], ans[maxn];

struct item {
    int t, v;
    bool operator < (const item & rhs) const {
        return v < rhs.v;
    }
} I[maxn];

LL res;
priority_queue<item> q;

int main() {
#ifdef Wearry
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; ++i) scanf("%d", &I[i].v), I[i].t = i;
    for(int i = 1; i <= n+k; ++i) {
        if(i <= n) q.push(I[i]);
        if(i >= k+1 && q.size()) {
            item tmp = q.top(); q.pop();
            ans[tmp.t] = i;
            res += 1LL * (i - tmp.t) * tmp.v;
        }
    }
    printf("%I64d\n", res);
    for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);

    return 0;
}

