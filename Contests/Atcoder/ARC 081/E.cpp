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
const int maxn = 200000 + 10;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}
 
char st[maxn];
int nxt[maxn][26], len;
int step[maxn][26], s[maxn];
 
void printans(int u) {
    
    if(u == -1) return;
    for(int i = 0; i < 26; ++i) {
        if(step[u][i] == s[u]) {
            putchar(i + 'a');
            printans(nxt[u][i]); 
            break;
        }
    }
}
 
int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif
 
    scanf("%s", st + 1);
    len = strlen(st + 1);
    for(int i = len; i >= 0; --i) {
        for(int j = 0; j < 26; ++j) 
            nxt[i][j] = (i == len) ? -1 : nxt[i+1][j];
        if(i < len) nxt[i][st[i+1] - 'a'] = i+1;
 
        s[i] = INT_MAX;
        for(int j = 0; j < 26; ++j) {
            if(nxt[i][j] != -1) 
                step[i][j] = (i == len) ? 0 : s[nxt[i][j]] + 1;
            chkmin(s[i], step[i][j]);
        }
    }
    printans(0);
 
    return 0;
}
