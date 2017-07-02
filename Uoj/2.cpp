#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back

template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;
const int maxn = 1e5 + 10;

template<typename T> T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48;
	return n * f;
}

struct Op {
    int x;
    char op[5];
}O[maxn];

int n, k;
signed main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++) 
        scanf("%s%d", O[i].op, &O[i].x);

    int tmp = 0, ans = 0;
    for(int b = 30; b >= 0; b--) {
        int x = 1, y = 0;

        for(int i = 1; i <= n; i++) {

            int t = O[i].x >> b & 1;

            if(O[i].op[0] == 'X') x ^= t, y ^= t;
            if(O[i].op[0] == 'O') x |= t, y |= t;
            if(O[i].op[0] == 'A') x &= t, y &= t;
        }

        if(x > y && tmp + (1<<b) <= k) {
            ans += (x<<b);
            tmp += (1<<b); 
        }else ans += (y<<b);
    }

    printf("%d\n", ans);
    return 0;
}
