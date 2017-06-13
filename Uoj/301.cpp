#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back

template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int maxn = 5e4 + 5;
const int maxq = 2e5 + 5;
const int oo = 0x3f3f3f3f;

template<typename T> T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

namespace bit {
    int c[maxn];
#define lowbit(x) ((x) & (-x))
    void add(int x) {
        for(int i = x; i < maxn; i += lowbit(i)) ++ c[i];
    }
    int query(int x) {
        int ans = 0;
        for(int i = x; i > 0; i -= lowbit(i)) ans += c[i];
        return ans;
    }
}

const int block_size = 233;

struct Young_Table {
    vector<int> A[block_size];

    pii insert(int x) {
        for(int i = 1; i < block_size; i++) {
            if(!A[i].size() || x > A[i].back()) {
                A[i].pb(x);
                return pii(i, (int)A[i].size());
            }else swap(x, *lower_bound(A[i].begin(), A[i].end(), x));
        }
        return pii(0, 0);
    }
}Inc, Dec;

void Insert(int x) {
    static int l;
    l = Dec.insert(-x).fst;
    if(l && l < block_size) bit::add(l);
    l = Inc.insert(x).snd;
    if(l >= block_size) bit::add(l);
}

int n, q, m, k;
vector<pii> Query[maxn];

int p[maxn], a[maxn], ans[maxq];
bool cmp(int x, int y) { return a[x] == a[y] ? x > y : a[x] < a[y]; }

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) p[i] = i, scanf("%d", a + i);

    sort(p + 1, p + n + 1, cmp);
    for(int i = 1; i <= n; i++) a[p[i]] = i;

    for(int i = 1; i <= q; i++) { 
        scanf("%d%d", &m, &k); 
        Query[m].push_back(pii(k, i)); 
    }

    for(int i = 1; i <= n; i++) {
        Insert(a[i]);
        for(const auto& x : Query[i]) 
            ans[x.snd] = bit::query(x.fst);
    }
    for(int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}
