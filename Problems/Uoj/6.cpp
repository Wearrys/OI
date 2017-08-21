#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back
#define getchar getchar_unlocked

template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;
const int maxn = 5e3 + 2;

template<typename T> inline T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48;
	return n * f;
}

int N, n, m, q;
int T[maxn * maxn];
int L[maxn], R[maxn];
int pos[maxn * maxn];

int x;
LL a, b, c, d;

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    x = read<int>(); a = read<LL>();
    b = read<LL>(); c = read<LL>(); d = read<LL>();
    n = read<int>(); m = read<int>(); q = read<int>();

    N = n * m;
    for(int i = 0; i < N; ++i) {
        T[i] = i;
        LL tmp = ((a*x+b)*x + c) % d;
        swap(T[i], T[(x = tmp) % (i+1)]);
    }
    while(q--) swap(T[read<int>()-1], T[read<int>()-1]);

    for(int i = 0; i < n; ++i) R[i] = m-1;
    for(int i = 0; i < N; ++i) pos[T[i]] = i;

    int tot = 0;
    for(int i = 0; i < N; ++i) {
        static int X, Y;
        X = pos[i] / m;
        Y = pos[i] % m;

        if(L[X] <= Y && Y <= R[X]) {
            for(int j = 0; j < X; ++j) chkmin(R[j], Y);
            for(int j=X+1; j < n; ++j) chkmax(L[j], Y);
            printf("%d ", i + 1);
            if(++tot == n+m-1) break;
        }
    }
    return 0;
}
