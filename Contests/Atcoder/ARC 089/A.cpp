#include <bits/stdc++.h>
 
using std::pair;
using std::vector;
using std::string;

typedef long long ll;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb(a) push_back(a)
#define mp(a, b) std::make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const int oo = 0x3f3f3f3f;
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

int n, t, x, y, la, lb;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif 

    read(n);
    for(int i = 1; i <= n; ++i) {
        read(t); read(x), read(y);

        int a = x + y, b = x - y;

        if((a&1) == (t&1) && (b&1) == (t&1)) {}
        else return !puts("No");

        a = (a + t) >> 1;
        b = (b + t) >> 1;

        if(a <= t && a >= la && b <= t && b >= lb) {
            la = a, lb = b;
        }
        else return !puts("No");
    }
    puts("Yes");

    return 0;
}
