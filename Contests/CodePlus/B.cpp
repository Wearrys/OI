#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp> //__gnu_pbds::priority_queue
 
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
 
const int N = 100000;
const int oo = 0x3f3f3f3f;
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

int n, m;
int s[N + 5];
pii x[N + 5];

int main() {
    //freopen("B.in", "r", stdin);
    
    read(n), read(m);
    for(int i = 1; i <= m; ++i) {
        read(x[i].fst), read(x[i].snd);
    }

    std::sort(x + 1, x + m + 1);

    ll ans = 0;

    for(int i = 1, j; i <= m; i = j + 1) {
        j = i;
        while(j < m && x[j+1].fst == x[j].fst + 1) ++ j;

        for(int b = 0; b < 31; ++ b) {
            int cnt = 0;
            bool pre = 0;

            for(int k = i; k <= j; ++k) {
                cnt += (pre ^= (x[k].snd >> b & 1));
            }

            if(x[i].fst != 1) cnt = std::min(cnt, j - i + 1 - cnt + 1);
            
            ans += ll(cnt) << b;
        }
    }
    printf("%lld\n", ans);

    return 0;
}
