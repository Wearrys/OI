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

const int N = 150000;

int n;
bool notprime[N + 5];
int prime[N + 5], pcnt;
int a[N + 5], b[N + 5];

void chk(int x) {
    for(int i = 1; i <= n; ++i) if((a[i] % x) && (b[i] % x)) return;
    printf("%d\n", x);
    exit(0);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    for(int i = 2; i <= N; ++i) if(!notprime[i]) {
        prime[pcnt ++] = i; 
        for(int j = i; (ll) j * i <= N; ++j) notprime[i * j] = true; 
    }
    for(int i = 1; i <= n; ++i) read(a[i]), read(b[i]);

    int x = a[1];
    for(int i = 0; i < pcnt; ++i) if(x % prime[i] == 0) {
        chk(prime[i]);
        while(x % prime[i] == 0) x /= prime[i];
    }
    if(x > 1) chk(x);

    x = b[1];
    for(int i = 0; i < pcnt; ++i) if(x % prime[i] == 0) {
        chk(prime[i]);
        while(x % prime[i] == 0) x /= prime[i];
    }
    if(x > 1) chk(x);
    puts("-1");
    return 0;
}
