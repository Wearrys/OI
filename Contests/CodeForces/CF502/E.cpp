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
 
const int mo = 1e9 + 7;
const int oo = 0x3f3f3f3f;
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

const int N = 200000;

typedef struct Point {
    int x, y;
    Point() { }
    Point(int x_, int y_): x(x_), y(y_) { }
} Vector; 

ll dot(const Vector& a, const Vector& b) {
    return 1ll * a.x * b.x + 1ll * a.y * b.y;
}
ll cross(const Vector& a, const Vector& b) {
    return 1ll * a.x * b.y - 1ll * a.y * b.x;
}
bool operator < (const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
Point operator + (const Point& a, const Point& b) {
    return Point(a.x + b.x, a.y + b.y);
}
Point operator - (const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y);
}

int n, m;
Point P0[N + 5], P1[N + 5];

void input() {
    int x, y;
    read(n), read(m);
    for(int i = 1; i <= n; ++i) read(x), read(y), P0[i] = Point(x, y);
    for(int i = 1; i <= m; ++i) read(x), read(y), P1[i] = Point(x, y);
}

void get_convex(Point* p, int& cnt) {
    std::sort(p + 1, p + cnt + 1);

    int top = 0, bot = 1;
    Point stk[N + 5];

    for(int i = 1; i <= cnt; ++i) {
        while(top > bot && cross(p[i] - stk[top-2], stk[top-1] - stk[top-2]) >= 0) -- top;
        stk[top++] = p[i];
    }
    bot = top;
    for(int i = cnt - 1; i >= 1; --i) {
        while(top > bot && cross(p[i] - stk[top-2], stk[top-1] - stk[top-2]) >= 0) -- top;
        stk[top++] = p[i];
    }

    for(int i = 1; i < top; ++i) {
        p[i] = stk[i] - stk[i-1];
    }
    cnt = top - 1;
}

int get_p(ll* s, int l)  {  
	int i = 0, j = 1, k = 0;
	while(i < l && j < l) {
        k = 0;
		while(s[i+k] == s[j+k] && k<l) k++;

		if(k == l) return i;
		if(s[i+k] > s[j+k]) {
            if(i+k+1>j) i=i+k+1; else i=j+1;
        } else if(j+k+1>i) j=j+k+1; else j=i+1; 
	}
	if(i<l) return i; else return j;
} 

void solve() {
    get_convex(P0, n);
    get_convex(P1, m);

    if(n != m) {
        puts("NO");
        return;
    }

    if(n == 2) {
        puts(dot(P0[1], P0[1]) == dot(P1[1], P1[1]) ? "YES" : "NO");
        return;
    }

    static ll p0[N + 5], p1[N + 5];
    for(int i = 0; i < n; ++i) 
        p0[i << 1] = (cross(P0[i == 0 ? n : i], P0[i + 1])), p0[i << 1 | 1] = (dot(P0[i + 1], P0[i + 1]));
    for(int i = 0; i < n; ++i) 
        p1[i << 1] = (cross(P1[i == 0 ? n : i], P1[i + 1])), p1[i << 1 | 1] = (dot(P1[i + 1], P1[i + 1]));

    int x = get_p(p0, n * 2), y = get_p(p1, n * 2);

    bool flag = true;
    for(int i = 0; i < n * 2; ++i) {
        if(p0[x] != p1[y]) { 
            flag = false; break; 
        } else { 
            (++ x) %= (n * 2); 
            (++ y) %= (n * 2); 
        }
    }
    puts(flag ? "YES" : "NO");
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    input();
    solve();

    return 0;
}
