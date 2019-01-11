#include <bits/stdc++.h>

using std::pair;
using std::vector;
using std::string;
using std::complex;

typedef long long ll;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb(a) push_back(a)
#define mp(a, b) std::make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define double long double

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

struct Complex {
    double real, imag;
    Complex(double r = 0.0, double i = 0.0): real(r), imag(i) {}
    Complex operator + (const Complex& rhs) const { return Complex(real + rhs.real, imag + rhs.imag); }
    Complex operator - (const Complex& rhs) const { return Complex(real - rhs.real, imag - rhs.imag); }
    Complex operator * (const Complex& rhs) const { return Complex(real*rhs.real - imag*rhs.imag, real*rhs.imag + imag*rhs.real); }
    Complex operator / (const double& div) const { return Complex(real / div, imag / div); }
};

const int N = 1 << 18;
const int mo = 998244353;

namespace Poly {
    const double PI = acos(-1.0);

    int n;
    void init(int m) {
        n = m;
        while(n > (n & -n)) n += (n & -n);
    }

    Complex w[2 * N + 5];
    void getw() {
        for(int i = 0; i <= 2 * N; ++i) {
            w[i] = Complex(cosl(i * PI / N), sinl(i * PI / N));
        }
    }

    void dft(Complex *x, int ty) {
        for(int i = 0, j = 0; i < n; ++i) {
            if(i < j) std::swap(x[i], x[j]);
            for(int l = n >> 1; (j ^= l) < l; l >>= 1);
        }

        for(int l = 1; l < n; l <<= 1) {
            int step = N / l;
            for(int i = 0; i < n; i += (l << 1)) {
                for(int j = 0; j < l; ++j) {
                    Complex t = x[i + j + l] * ((ty == 1) ? w[j * step] : w[2 * N - j * step]);
                    x[i + j + l] = (x[i + j] - t);
                    x[i + j] = (x[i + j] + t);
                }
            }
        }
        if(ty == -1) {
            for(int i = 0; i < n; ++i) {
                x[i] = x[i] / (double) n;
            }
        }
    }
}

typedef vector<int> poly;

int p;
poly operator * (const poly& a, const poly& b) {
    using namespace Poly;
    static Complex tx[N + 5], ty[N + 5];

    int la = a.size(), lb = b.size();
    init(la + lb - 1);
    for(int i = 0; i < n; ++i) tx[i] = (i < la) ? a[i] : 0;
    for(int i = 0; i < n; ++i) ty[i] = (i < lb) ? b[i] : 0;

    dft(tx, +1);
    dft(ty, +1);

    for(int i = 0; i < n; ++i) tx[i] = tx[i] * ty[i];

    dft(tx, -1);

    poly c; c.resize(la + lb - 1);
    for(int i = 0; i < (la + lb - 1); ++i) {
        c[i] = ((ll) std::round(tx[i].real)) % p;
    }
    return c;
}

ll n;

poly solve(int l, int r) {
    if(l == r) return (poly) { 1, l };
    int mid = (l + r) >> 1;
    return solve(l, mid) * solve(mid+1, r);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("ans", "w", stdout);
#endif

    std::cin >> n >> p;

    if(p == 2) {
        ll m = (n + 1) / 2, ans = 1;
        for (int i = 0; i < 63; ++i) if(m >> i & 1) {
            (ans *= 2) %= mo; 
        }
        printf("%lld\n", (n + 1 - ans) % mo);
        printf("%lld\n", ans);           
        return 0;
    }

    Poly::getw();
    poly res = solve(1, n);
    static int ans[N + 5] = {0};
    for(int i = 0; i <= n; ++i) ++ ans[res[i]];
    for(int i = 0; i < p; ++i) printf("%d\n", ans[i]);

    return 0;
}
