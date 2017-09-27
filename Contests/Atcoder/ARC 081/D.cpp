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
const int maxn = 100000 + 10;
const int mod = 1e9 + 7;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}
 
int n;
vector<int> a;
char u[maxn], d[maxn];
 
int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif
 
    scanf("%d", &n);
    scanf("%s", u);
    scanf("%s", d);
 
    for(int i = 0; i < n; ) {
        if(u[i] == d[i]) {
            ++ i;
            a.pb(0);
        }else {
            i += 2;
            a.pb(1);
        }
    }
 
    LL res = 1;
    for(int i = 0; i < int(a.size()); ++i) {
        if(i == 0) {
            if(a[i]) res = res * 6 % mod;
            else res = res * 3 % mod;
        }else {
            if(a[i]) {
                if(a[i-1]) res = res * 3 % mod;
                else res = res * 2 % mod;
            }else {
                if(a[i-1]) {}
                else res = res * 2 % mod;
            }
        }
    }
    printf("%lld\n", res);
    return 0;
}
