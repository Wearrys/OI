#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb push_back
#define eb emplace_back
#define REP(i, a, b)  for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i=(a-1), i##end = (b); i >=i##end; --i)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const int N = 300000;
const int oo = 0x3f3f3f3f;
const int mod = 998244353;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

LL fpm(LL base, LL exp) {
    LL res = 1;
    for(; exp > 0; exp >>= 1) {
        if(exp & 1) 
            res = res * base % mod;
        base = base * base % mod;
    }
    return res;
}

int cnt[4];
char st[N + 5];
LL fac[N + 5], inv[N + 5];

inline LL C(int n, int k) {
    return fac[n] * inv[k] % mod * inv[n - k] % mod;
}

int n, m;
bool a[N + 5], b[N + 5], c[N + 5], d[N + 5];

LL calc() {
    LL pre = 1, res = 0;
    int lu = 0, ld = 0, ru = cnt[2], rd = cnt[3];
    for(int i = 0; i < m; ++i) {
        if(c[i]) lu ++, ru --;
        if(d[i]) ld ++, rd --;
        if(c[i] && d[i]) { (pre <<= 1LL) %= mod; }

        if(c[i] || d[i]) { 
            res = (res + pre*(cnt[1] ? C(cnt[1]+ru+rd - 1, cnt[1] - 1) : (ru + rd == 0))) % mod;
            pre = (pre + (cnt[0] ? C(cnt[0]+lu+ld - 1, cnt[0] - 1) : (lu + ld == 0))) % mod;
        }
    }
    return res;
}

void Input() {
    cin >> n >> m;
    scanf("%s", st); for(int i = 0; i < n; ++i) cnt[0] += (a[i] = st[i] - '0');
    scanf("%s", st); for(int i = 0; i < n; ++i) cnt[1] += (b[i] = st[i] - '0');
    scanf("%s", st); for(int i = 0; i < m; ++i) cnt[2] += (c[i] = st[i] - '0');
    scanf("%s", st); for(int i = 0; i < m; ++i) cnt[3] += (d[i] = st[i] - '0');
    if(!(cnt[0] + cnt[1] + cnt[2] + cnt[3])) puts("1"), exit(0);
}

void Init() {
    fac[0] = 1;
    for(int i = 1; i <= N; ++i) fac[i] = fac[i-1] * i % mod;
    inv[N] = fpm(fac[N], mod - 2);
    for(int i = N; i >= 1; --i) inv[i-1] = inv[i] * i % mod;
}

void Solve() {
    LL Ans = calc();

    swap(n, m); swap(b, c);
    swap(a, d); swap(a, b);
    swap(cnt[0], cnt[3]);
    swap(cnt[1], cnt[2]);
    swap(cnt[0], cnt[1]);

    Ans = (Ans + calc()) % mod;
    printf("%lld\n", Ans);
}

int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    Init();
    Input();
    Solve();

    return 0;
}
