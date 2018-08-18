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

string procStatus() {
    std::ifstream t("/proc/self/status");
    return string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}

template <typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = 200000;

int n;
int a[N + 5];
ll s[N + 5];
ll ans = LLONG_MAX;

using namespace std;
int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    for(int i = 1; i <= n; ++i) s[i] = s[i-1] + read(a[i]);

    int x = 1, y = 3;
    for(int i = 2; i < n; ++i) {

        while(x+1 < i && abs(s[x+1]-(s[i]-s[x+1])) <= abs(s[x]-(s[i]-s[x]))) {
            ++ x;
        }
        chkmax(y, i + 1);
        while(y+1 < n && abs(s[n]-s[y+1]-(s[y+1]-s[i])) < abs(s[n]-s[y]-(s[y]-s[i]))) {
            ++ y;
        }

        ll mx = max(max(s[x], s[i]-s[x]), max(s[y]-s[i], s[n]-s[y]));
        ll mn = min(min(s[x], s[i]-s[x]), min(s[y]-s[i], s[n]-s[y]));

        chkmin(ans, mx - mn); 
    }
    printf("%lld\n", ans);

    return 0;
}
