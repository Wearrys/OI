#include <bits/stdc++.h>
using namespace std;

const int N = 200000 + 5;

int n, a[200005], q[200005], las[200005], par[200005], ed[200005];

stack<int> w;

long long ans[200005];

struct Line {
    long long k, b;

    Line(long long _k = 0, long long _b = 0): k(_k), b(_b) { }
    long long operator () (int x) {
        return 1ll * k * x + b;
    }
};

Line f[N << 2];

void upd(int u, int l, int r, int x, int y, Line g) {
    int mid = (l + r) >> 1;

    if (x <= l && r <= y) {

        if (g(r) > f[u](r)) swap(f[u], g);

        if (f[u](l) >= g(l)) return;
        else if (f[u](mid) < g(mid)) {
            swap(f[u], g);
            upd(u << 1 | 1, mid + 1, r, x, y, g);
        } else {
            upd(u << 1, l, mid, x, y, g);
        }

        return;
    }

    if (x <= mid) upd(u << 1, l, mid, x, y, g);
    if (mid < y) upd(u << 1 | 1, mid +1, r, x, y, g);
}

long long qry(int u, int l, int r, int x) {
    int mid = (l + r) >> 1;
    if (l == r) return f[u](x);
    return max(f[u](x), x <= mid ? qry(u << 1, l, mid, x) : qry(u << 1 | 1, mid+1, r, x));
}

int main() {

#ifdef Wearry
    freopen("in", "r", stdin);
#endif

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
	w.push(0);
	for (int i = 1; i <= n; i++) {
		while (w.size() && a[w.top()] >= a[i]) w.pop();
		las[i] = w.top();
		w.push(i);
	}

    int l = 1, r = 0;
	q[1] = 0;

    for (int i = 1; i <= n; i++) {
        while (r >= 1 && a[i] <= a[q[r]]) {
            ed[q[r]] = i-1;
            r--;
        }
        ans[i] = 1ll * a[i] * (i - q[r]);
        q[++r] = i;
    }

    while (r >= 1) {
        ed[q[r]] = n;
        --r;
    }

    for (int i = 1; i <= n; ++i) {
        upd(1, 1, n, i, ed[i], Line(a[i], 1ll * (-las[i]) * a[i]));
        ans[i] = max(ans[i], qry(1, 1, n, i));
        printf("%lld\n", ans[i] = max(ans[i], ans[i-1]));
    }

    return 0;
}
