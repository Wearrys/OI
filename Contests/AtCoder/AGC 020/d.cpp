#include <bits/stdc++.h>
 
using std::pair;
using std::vector;
using std::string;

typedef long long ll;
typedef pair<int, int> pii;
 
#define int ll
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

const int N = 100000;

int getlen(int a, int b) {
    int t;
    if(a >= b) {
        t = (a + b) / (b + 1);
    } else {
        t = (a + b) / (a + 1);
    }
    return t;
}

int T;
int a, b, c, d, t;

bool chk(int x, int y) {
    if(x < 0 || y < 0) return false;
    if(x == 0) return y + 1 <= t;
    return x <= t && y <= t;
}

signed main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif 
    
    read(T);
    while(T--) {
        static int ta, tb, lb, la;
        read(a), read(b), read(c), read(d);
        t = getlen(a, b);

        int l = 0, r = a;
        while(l < r) {
            int mid = (l + r + 1) >> 1;

            ta = a - mid*t;

            if(ta >= 0) 
                tb = (b - mid + 1 + ta) / (ta + 1);
            else 
                tb = oo;

            if(tb <= t) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }

        ta = l;
        tb = (b - l) / t;
        lb = (b - l - t*tb);
        if(!lb && tb) { -- tb; lb = t; }

        la = (a - t*l - tb);
        //debug("%d %d %d %d %d\n", t, ta, tb, la, lb);

        for(int i = c; i <= d; ++i) {
            if(i <= ta * (t + 1)) {
                putchar(i % (t + 1) == 0 ? 'B' : 'A');
            } else if(i <= ta * (t + 1) + la + lb) {
                putchar(i - ta * (t + 1) <= la ? 'A' : 'B');
            } else {
                putchar((i - ta * (t + 1) - la - lb) % (t + 1) == 1 ? 'A' : 'B');
            }
        }
        puts("");
    }
    return 0;
}
