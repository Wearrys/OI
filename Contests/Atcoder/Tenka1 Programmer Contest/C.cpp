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
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

LL n;
int main() {
#ifdef Wearry
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif 

    n = read<LL>();

    for(int i = 1; i <= 3500; ++i)
        for(int j = 1; j <= 3500; ++j) {
            LL X = 4LL*i*j - n*j - n*i, Y = n * i * j;

            if(X > 0 && Y % X == 0) {
                printf("%d %d %lld\n", i, j, Y / X);
                return 0;
            }
        }
    return 0;
}
