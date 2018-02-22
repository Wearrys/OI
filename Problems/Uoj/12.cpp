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
 
const int N = 100 + 10;
const int oo = 0x3f3f3f3f;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

long long solve(long long n) {
    return (long long)(sqrt(n)) << 1LL;
}

int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif 

    long long a, b;
    for(int T = read<int>(); T--; ) {
        scanf("%lld%lld", &a, &b);
        printf("%lld %lld\n", a * solve(b / a), a + b);
    }

    return 0;
}
