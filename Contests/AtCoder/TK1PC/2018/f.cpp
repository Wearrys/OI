#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pb push_back

const int N = 300000;
const int mo = 998244353;

void fail() { puts("0"); exit(0); }

int n;
int ty[N + 5];
int a[N + 5], b[N + 5];
int l[N + 5], r[N + 5];

void input() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }

    if(*min_element(a, a + n) != 1) { fail(); }
    if(*max_element(a, a + n) == 1) { 
        int res = 1;
        for(int i = 1; i <= n; ++i) res = (ll) res * i % mo;
        printf("%d\n", res);
        exit(0);
    }
    
    for(int i = n - 1; i >= 0; --i) if(a[i] == 1 && (i == 0 || a[i-1] != 1)) {
        for(int j = 0; j < n; ++j) b[j] = a[(i + j) % n];
        break;
    }

    memcpy(a, b, sizeof a);
    memset(l, -1, sizeof l);

    for(int i = 0; i < n; ++i) {
        int x = a[i];
        if(i == 0 || a[i] != a[i-1]) {
            if(~l[x]) { fail(); }
            l[x] = i;
        } r[x] = i;
    }
}

int mx[(N << 2) + 5];
void modify(int x, int y, int v, int u = 1, int L = 0, int R = n - 1) {
    if(x <= L && R <= y) {
        mx[u] = max(mx[u], v);
    } else {
        int mid = (L + R) >> 1;
        if(x <= mid)
            modify(x, y, v, u << 1, L, mid);
        if(mid < y)
            modify(x, y, v, u << 1 | 1, mid+1, R);
    }
}

int query(int p, int u = 1, int L = 0, int R = n - 1) {
    if(L == R) return mx[u];
    int mid = (L + R) >> 1;
    return std::max(mx[u], (p <= mid) ? query(p, u << 1, L, mid) : query(p, u << 1 | 1, mid+1, R));
}

void solve() {
    for(int i = 0; i <= (N << 2); ++i) { mx[i] = 1; }

    vector<int> seq;
    for(int i = 0; i < n; ++i) {
        if(!seq.empty() && a[i] == seq.back())
            continue;
        seq.pb(a[i]);
    }

    static bool vis[N + 5];
    int len = r[1] - l[1], ans = 1;

    for(int i = 0; i < (int) seq.size(); ++i) {
        if(r[seq[i]] - l[seq[i]] > len) fail();

        if(i == 0 || seq[i-1] > seq[i]) { ty[i] |= 1; }
        if(i+1 < (int) seq.size() && seq[i + 1] > seq[i]) { ty[i] |= 2; }

        if(ty[i] == 3 && r[seq[i]] - l[seq[i]] != len) fail();
        if(ty[i] == 0) ans = (ll) ans * (len - (r[seq[i]] - l[seq[i]]) + 1) % mo;

        modify(l[seq[i]]-len, r[seq[i]], seq[i]);

        if(ty[i] == 0) vis[l[seq[i]]] = true;
        if(ty[i] == 1) vis[l[seq[i]]] = true;
        if(ty[i] == 3) vis[l[seq[i]]] = true;
        if(ty[i] == 2) vis[r[seq[i]] - len] = true;
    }

    vector<int> lim;
    for(int i = 0; i < n; ++i) if(!vis[i]) {
        lim.pb(query(i)); 
    }

    std::sort(lim.begin(), lim.end());

    int cur = 0;
    for(int i = n; i >= 1; --i) {
        if(!~l[i]) { ++ cur; }
        while(!lim.empty() && lim.back() == i) {
            ans = (ll) ans * (cur --) % mo;
            lim.pop_back();
        }
    }
    printf("%d\n", ans);
}

int main() {

    input();
    solve();

    return 0;
}
