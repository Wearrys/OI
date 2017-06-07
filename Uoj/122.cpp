#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back

template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int maxn = 2e6 + 10;
const int oo = 0x3f3f3f3f;

template<typename T> T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48;
	return n * f;
}

int n;
int dfn[maxn], bfn[maxn], mn[maxn], mx[maxn];

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    n = read<int>();
    for(int i = 1; i <= n; i++) dfn[read<int>()] = i;
    for(int i = 1; i <= n; i++) bfn[i] = dfn[read<int>()];

    mn[n+1] = -(mx[n+1] = -oo);
    for(int i = n; i >= 2; i--) 
        mn[i] = min(mn[i+1], bfn[i]),
        mx[i] = max(mx[i+1], bfn[i]);

    int ans = 2;
    for(int i = 2; i <= n; i++) {
        if(bfn[i+1] < bfn[i]) { ans += 2; }
        if(bfn[i]+1 == bfn[i+1] && mx[i+1] - mn[i+1] + 1 == n - i - 1 + 1) 
            ++ ans;
    }
    printf("%d.%d00\n", ans >> 1, (ans & 1) * 5);
    return 0;
}
