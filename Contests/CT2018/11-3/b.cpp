#include <bits/stdc++.h>
using namespace std;

const int L = 5;
const int N = 20;
const int mo = 1e9 + 9;

#define fst first
#define snd second

typedef long long ll;

struct point {
    int x, y;

    point operator - (const point& b) const {
        return (point) {x - b.x, y - b.y};
    }
    friend ll cross(const point& a, const point& b) {
        return (ll) a.x * b.y - (ll) a.y * b.x;
    }
};

int T, n;
point p[N + 5];
int g[L + 5], f[L + 5], h[L + 5], s[L + 5];

struct poly {
    int v[L];

    int &operator [](int x) { return v[x]; }
    int operator [](int x) const { return v[x]; }

    poly() { }
    poly(const int *t_v) { memcpy(v, t_v, sizeof v); }
    poly(int v0, int v1 = 0) {
        memset(v, 0, sizeof v), v[0] = v0, v[1] = v1;
    }

    int val() const {
        int res = 0;
        for(int i = 0; i < L; ++i) 
            res = (res + (ll) v[i] * s[i]) % mo;
        return res;
    }
};

poly operator + (const poly& a, const poly& b) {
    poly c;
    for(int i = 0; i < L; ++i) 
        c[i] = (a[i] + b[i]) % mo;
    return c;
}

poly operator - (const poly& a, const poly& b) {
    poly c;
    for(int i = 0; i < L; ++i) 
        c[i] = (a[i] - b[i] + mo) % mo;
    return c;
}

poly operator * (const poly& a, const poly& b) {
    int c[L << 1] = { 0 };
    for(int i = 0; i < L; ++i) {
        for(int j = 0; j < L; ++j) {
            c[i + j] = (c[i + j] + (ll) a[i] * b[j]) % mo;
        }
    }
    for(int i = (L << 1) - 2; i >= L; --i) {
        for(int j = 0; j < L; ++j) {
            c[i - j - 1] = (c[i - j - 1] + (ll) c[i] * h[j]) % mo;
        }
    }
    return c;
}

struct matrix {
    poly p0, p1;
    matrix(int v): p0(v), p1(0) { }
    matrix(const poly &_p0, const poly &_p1): p0(_p0), p1(_p1) { }
};

matrix operator + (const matrix &a, const matrix &b) { return matrix(a.p0 + b.p0, a.p1 + b.p1); }
matrix operator * (const matrix &a, const matrix &b) { return matrix(a.p0 * b.p0, a.p1 + a.p0 * b.p1); }

template <typename T>
T fpm(T x, int y) {
    T ans = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            ans = ans * x;
        x = x * x;
    }
    return ans;
}

matrix calc(int a, int b, matrix P, matrix Q) {
    if(!a)
        return fpm(Q, b);
    else if(!b)
        return fpm(P, a);
    else if(a < b) 
        return calc(a, b % a, P * fpm(Q, b / a), Q);
    else 
        return calc(a % b, b, P, fpm(P, a / b) * Q);
}

poly calc(int a, int b) {
    poly res(0), x(0, 1);
    for(int i = 0; i < a; ++i) {
        res = res + fpm(x, i * b / a);
    }
    return res;
}

void input() {
    scanf("%d", &n);
    for(int i = 0; i < 4; ++i) scanf("%d", g + i);
    for(int i = 0; i < 4; ++i) scanf("%d", f + i), s[i + 1] = (s[i] + f[i]) % mo;
    for(int i = 0; i < n; ++i) scanf("%d%d", &p[i].x, &p[i].y), p[i].y += p[i].x;

    h[0] = g[0] + 1;
    for(int i = 1; i <= 4; ++i) {
        h[i] = (g[i] - g[i - 1] + mo) % mo;
    }
}

pair<point, point> l[N + 5];

void solve() {
    int e = 0;
    for(int i = 0; i < n; ++i) {
        point a = p[i], b = p[(i + 1) % n];
        if(a.x != b.x) l[e ++] = make_pair(a, b);
    }

    int ans = 0;
    poly x(0, 1);
    matrix P(1, 1), Q(x, 0);

    for(int i = 0; i < e; ++i) {
        const point a = l[i].fst, b = l[i].snd;
        const point c = l[(i + 1) % e].fst, d = l[(i + 1) % e].snd;
        const int dx = abs(a.x - b.x), dy = abs(a.y - b.y);

        poly res = calc(dx, dy, P, Q).p1;
        poly bas = fpm(x, std::min(a.y, b.y));

        if(a.y > b.y) 
            res = res - 1 + fpm(x, dy);
        res = res * bas * x;

        if(a.x > b.x) {
            ans = (ans + res.val()) % mo;

            if(c.x < d.x) {
                if(c.y < b.y || (c.y == b.y && cross(d - c, a - c) > 0)) {
                    ans = (ans + fpm(x, b.y + 1).val()) % mo;
                } else 
                    ans = (ans + fpm(x, c.y).val()) % mo;
            } else if(c.y < b.y) {
                ans = ((ans + fpm(x, b.y + 1).val()) % mo - fpm(x, c.y + 1).val()) % mo; 
            }
        } else {
            ans = (ans - res.val()) % mo;

            int _ = __gcd(dx, dy);
            poly y = fpm(x, dy / _);
            poly r = fpm(matrix(y, 1), _).p1;

            if(a.y > b.y)
                r = r * y;

            ans = (ans + (r * (bas * (x - 1))).val()) % mo;

            if(c.x > d.x) {
                if(c.y > b.y || (c.y == b.y && cross(d - c, a - c) > 0)) {
                    ans = (ans - fpm(x, b.y).val()) % mo;
                } else {
                    ans = (ans - fpm(x, c.y + 1).val()) % mo;
                }
            } else if(c.y > b.y) {
                ans = ((ans - fpm(x, b.y).val()) % mo + fpm(x, c.y).val()) % mo;
            }
        }
    }
    ans = (ans + mo) % mo;
    printf("%d\n", ans);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d", &T);

    while(T--) { 
        input(); 
        solve(); 
    }

    return 0;
}
