#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
typedef unsigned long long ull;
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

int n, k;
ull a[maxn], lb[maxn];

vector<ull> base;
void solve() {
    ull ans = 0, res = 0;
    REP(x, 0, 32)
        REP(y, 0, 32) {

            bool flag = 0;
            REP(i, 0, n) if(a[i] >> x & 1) { flag = true; break; }
            if(!flag) continue;

            flag = 0;
            REP(i, 0, n) if(a[i] >> y & 1) { flag = true; break; }
            if(!flag) continue;

            flag = 0;
            REP(i, 0, n) if((a[i]>>x&1) != (a[i]>>y&1)) flag = 1;

            if(x+y-1-flag < 0) ++ res;
            else ans += 1ull << (x+y-1-flag);
        }

    ans += res >> 1; res &= 1;
    printf("%llu", ans);
    puts(res ? ".5" : "");
}
void solve_2() {
    REP(i, 0, n) 
        DREP(j, 24, 0) if(a[i] >> j & 1ull) {
            if(!lb[j]) {
                base.pb(lb[j] = a[i]);
                break;
            }a[i] ^= lb[j];
        }

    ull ans = 0, res = 0;
    int all = base.size();
    REP(i, 0, 1<<all) {
        ull val = 0;
        REP(j, 0, all) if(i >> j & 1) val ^= base[j];

        ull A = 0, B = 1;
        REP(j, 0, k) {
            A *= val, B *= val; 
            A += B >> all, B &= (1 << all) - 1;
        }

        ans += A, res += B;
        ans += res >> all, res &= (1 << all) - 1;
    }

    printf("%llu", ans);
    puts(res ? ".5" : "");
}

int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif
    
    scanf("%d%d", &n, &k);
    REP(i, 0, n) scanf("%llu", a + i);

    if(k == 1) {
        ull s = 0;
        REP(i, 0, n) s |= a[i];
        printf("%llu", s >> 1);
        puts(s&1 ? ".5" : "");
    }
    else if(k == 2) solve();
    else if(k >= 3) solve_2(); 
    return 0;
}
