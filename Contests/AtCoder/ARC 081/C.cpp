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
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}
 
int n;
vector<LL> vec;
map<int, bool> mp;
 
int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif
 
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) { 
        LL x = read<int>();
        if(mp[x]) {
            mp.erase(x);
            vec.pb(x);
        }else mp[x] = true;
    }
 
    sort(vec.begin(), vec.end(), greater<LL>());
 
    if(vec.size() > 1) 
        printf("%lld\n", vec[0] * vec[1]);
    else printf("0\n");
 
    return 0;
}
