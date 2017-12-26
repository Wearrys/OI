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

ll calc(ll x, ll p, ll m) {
    if(x < m) return 0;
    return (x - m) / p + 1;
}

ll gcd(ll a, ll b) {
    return (!a) ? b : gcd(b % a, a);
}

void exgcd(ll a, ll b, ll& x, ll &y) {
    if(!b) x = 1, y = 0;
    else {
        exgcd(b, a%b, y, x);
        y -= (a/b) * x;
    }
}

ll calc(ll a, ll b, ll c, ll l, ll r) {
    ll g = gcd(a, b);
    if(c % g) return 0;
    a /= g, b /= g, c /= g;

    ll x, y;
    exgcd(a, b, x, y);
    x = x * c % b;
    x = (x % b + b) % b;
    return calc(r, b, x) - calc(l-1, b, x);
}

struct Matrix {
    ll x[2][2];
    Matrix(int t = 0) { 
        memset(x, 0, sizeof x);
        if(t) x[0][0] = x[1][1] = 1;
    }
} A, X;

ll p; 
Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix c;
    for(int i = 0; i < 2; ++i) 
        for(int j = 0; j < 2; ++j) 
            for(int k = 0; k < 2; ++k) {
                c.x[i][j] = (c.x[i][j] + 1ll * a.x[i][k] * b.x[k][j]) % p;
            }
    return c;
}

ll i, l, r, k, m;

int main() {
#ifdef Wearry
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif 

    A.x[0][0] = A.x[0][1] = A.x[1][0] = 1;

    int T;
    std::cin >> T;

    while(T--) {
        std::cin >> i >> l >> r >> k >> p >> m;

        X = A;
        i %= p;
        Matrix Ans = 1;
        for(ll exp = k - 2; exp > 0; exp >>= 1ll) {
            if(exp & 1ll)
                Ans = Ans * X;
            X = X * X;
        }

        X = Ans;
        m -= 1ll * i * X.x[0][1] % p;
        m = (m % p + p) % p;

        printf("%lld\n", calc(X.x[0][0], p, m, l, r));
    }

    return 0;
}
