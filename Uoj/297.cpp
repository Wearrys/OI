#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back

template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int maxn = 2e7 + 5;
const int oo = 0x3f3f3f3f;

template<typename T> T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

bool p[maxn];
int cnt[maxn], ans[maxn];

int seed, n, k, S;
#define Rand() (seed = ((seed * 12321) ^ 9999) % 32768)

void Data() {
	scanf("%d%d%d", &k, &seed, &S);

	int t = 0; n = k * 2 + 1;
	for (int i = 1; i <= n; i++) t += (p[i] = (Rand() >> 7 & 1));

	int i = 1;
	while (t > k) { while (p[i] == 0) i++; p[i] = 0; t--; }
	while (t < k) { while (p[i] == 1) i++; p[i] = 1; t++; }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif
    Data();

    int tot = 0, h = 5e6;
    for(int i = 1; i < n; i++) {
        if(!p[i+1]) ans[i+1] += tot;
        tot = p[i+1] ? tot - cnt[++h]++ : tot + cnt[h--];
    }

    tot = 0;
    h = 5e6;
    memset(cnt, 0, sizeof cnt);

    int ans1 = 0, ans2 = 0, ans3 = 0;
    for(int i = n; i >= 1; i--) {
        if(!p[i]) {
            ans[i] += tot;
            if(ans[i] == 0) ans1 = i;
            if(ans[i] == S) ans2 = i;
            if(ans[i] == k - S) ans3 = i;
        }else ++ cnt[h];

        tot = !p[i] ? tot - cnt[++h] : tot + cnt[h--];
    }
    printf("%d\n%d\n%d\n", ans1, ans2, ans3);

    return 0;
}
