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
const int maxn = 100000 + 5;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int n, ans = 0;
bool vis[30];
char st[maxn];

int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    n = read<int>();
    scanf("%s", st);
    for(int i = 0; i < n; ++i) {

        int now = 0;
        memset(vis, 0, sizeof vis);

        for(int j = i; j >= 0; --j) {
            if(st[j] >= 'A' && st[j] <= 'Z') break;
            if(!vis[st[j] - 'a']) vis[st[j] - 'a'] = true, ++ now; 
        }
        chkmax(ans, now);
    }
    printf("%d\n", ans);

    return 0;
}
