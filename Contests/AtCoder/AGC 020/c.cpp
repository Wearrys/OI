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

const int N = 4000000;

int n, a;
std::bitset<N + 5> Set;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    // freopen("out", "w", stdout);
#endif 

    int sum = 0;

    read(n);
    Set.set(0);
    for(int i = 1; i <= n; ++i) {
        read(a);
        sum = (sum + a);
        Set = Set | (Set << a);
    }

    sum = (sum + 1) / 2;

    for(int i = sum; ; i++) {
        if(Set.test(i)) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}
