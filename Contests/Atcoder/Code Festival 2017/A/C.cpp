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
const int maxn = 1000 + 5;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int n, m;
int cnt[30];
char st[maxn][maxn];

int main() {
#ifdef Wearry
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        scanf("%s", st[i]);
        for(int j = 0; j < m; ++j) { cnt[st[i][j] - 'a'] ++; }
    }

    int t = 0, t1 = 0, x = 0;
    if(n & 1) t += m / 2;
    if(m & 1) t += n / 2;

    x = (n&1) && (m&1);

    t1 = (n * m - t * 2 - x) / 4;

    for(int i = 0; i < 26; ++i) {
        if(cnt[i] & 1) -- x, -- cnt[i];
        while(t1 && cnt[i] >= 4) cnt[i] -= 4, -- t1;
        while(t && cnt[i] >= 2) cnt[i] -= 2, -- t;
    }

    puts(x >= 0 && t1 == 0 && t == 0 ? "Yes":"No");

    return 0;
}

