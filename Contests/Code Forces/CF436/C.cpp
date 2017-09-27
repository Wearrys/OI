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
const int maxn = 100000 + 5;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int a, b, f, k;
int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    cin >> a >> b >> f >> k;

    if(k >= 1 && b < f) return puts("-1"), 0;
    if(k >= 1 && b < a-f) return puts("-1"), 0;
    if(k >= 3 && b < 2*f) return puts("-1"), 0;
    if(k >= 2 && b < 2*(a-f)) return puts("-1"), 0;

    int cur = b, tot = 0;
    for(int i = 1; i <= k; ++i) {
        if(i == k) {
            if(b < a) ++ tot;
            break;
        }

        if(i & 1) {
            if(b >= a + (a - f)) 
                b -= a;
            else if(b >= f) {
                ++ tot;
                b -= f, b = cur - (a - f);
            }
        }else {
            if(b >= a + f) 
                b -= a;
            else if(b >= a-f) {
                ++ tot;
                b -= a-f, b = cur - f;
            }
        }
    }
    printf("%d\n", tot);

    return 0;
}

