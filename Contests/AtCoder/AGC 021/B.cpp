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
const double PI = acos(-1.0);
const double eps = 1e-5;

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

double sqr(double x) { return x * x; }

const int N = 100;

struct P{
    int id;
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	friend P operator +(P a,P b){
		return P(a.x+b.x,a.y+b.y);
	}
	friend P operator -(P a,P b){
		return P(a.x-b.x,a.y-b.y);
	}
	friend double operator*(P a,P b){
		return a.x*b.y-a.y*b.x;
	}
	friend double operator/(P a,P b){
		return a.x*b.x+a.y*b.y;
	}
	friend bool operator==(P a,P b){
		return fabs(a.x-b.x)<eps&&fabs(a.y-b.y)<eps;
	}
	friend bool operator!=(P a,P b){
		return !(a==b);
	}
	friend bool operator<(P a,P b){
		if(fabs(a.y-b.y)<eps)return a.x<b.x;
		return a.y<b.y;
	}
	friend double dis2(P a){
		return sqr(a.x)+sqr(a.y);
	}
	friend void print(P a){
		printf("%.2lf %.2lf\n",a.x,a.y);
	}
};

double dot (P a, P b) {
    return a.x * b.x + a.y * b.y;
}

double len (P a) {
    return sqrt(1. * a.x * a.x + 1. * a.y * a.y);
}

double angle(P a, P b) {
    return acos(dot(a, b) / len(a) / len(b));
}

int n, m;
double ans[N + 5];
P p[N + 5], q[N + 5];

bool cmp(P a,P b)
{
	if(fabs((b-p[1])*(a-p[1]))<eps)return dis2(a-p[1])<dis2(b-p[1]);
	return (a-p[1])*(b-p[1])>0;
}

void graham()
{
	for(int i=1;i<=n;i++)
		if(p[i]<p[1])std::swap(p[i],p[1]);
    std::sort(p+2,p+n+1,cmp);
	q[++m]=p[1];q[++m]=p[2];
	for(int i=3;i<=n;i++)
	{
		while((q[m]-q[m-1])*(p[i]-q[m-1])<eps&&m>1)m--;
		q[++m]=p[i];
	}
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    if(n == 2) {
        printf("%.5lf\n%.5lf\n", 0.5, 0.5);
        return 0;
    }

    for (int i = 1; i <= n; ++ i) {
        static int x, y;
        read(x), read(y);

        p[i].id = i;
        p[i].x = x, p[i].y = y;
    }

    graham();
    if(m == 2) {
        for (int i = 1; i <= n; ++ i) printf("%.8lf\n", (i == q[1].id || i == q[2].id) ? 0.5 : 0);
        return 0;
    }

    for (int i = 1; i <= m; ++ i) {

        int lst = (i == 1) ? m : i - 1;
        int nxt = (i == m) ? 1 : i + 1;

        double ang = angle(q[nxt] - q[i], q[lst] - q[i]);

        while (ang < 0) ang += PI;
        while (ang > PI) ang -= PI;
        ans [q[i].id] = (PI - ang) / 2 / PI;

    }

    for (int i = 1; i <= n; ++ i) printf("%.8lf\n", ans[i]);

    return 0;
}

