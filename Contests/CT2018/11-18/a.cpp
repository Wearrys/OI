#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100000;
const int oo = 0x3f3f3f3f;

int n, s, t;
int x[N + 5];
ll ans = LLONG_MAX;

template <typename T> void chkmin(T& a, T b) { a = (a > b ? b : a); }

void solve() {
    priority_queue<int> q;
    priority_queue<int, vector<int>, greater<int> > d;

    ll sum = 0;
    for(int i = s + 1; i <= n; ++i) {
        int l = (i < n) + (s > 1), r = n - i + s - 1;

        if(l <= t && t <= r) 
            chkmin<ll>(ans, 2 * (x[n] - x[1]) - abs(x[i] - x[s]));
        else if(l <= t) {
            while(!d.empty() && !q.empty() && d.top() < q.top()) {
                int a = d.top(), b = q.top(); q.pop(); d.pop();
                q.push(a); d.push(b);
                sum += 2 * (a - b);
            }

            while((int) q.size() < t - r && !d.empty()) {
                sum += 2 * d.top();
                q.push(d.top()); d.pop();
            }

            if((int) q.size() >= t - r) {
                chkmin<ll>(ans, 2 * (x[n] - x[1]) - abs(x[i] - x[s]) + sum);
            }
        }

        if(i > s + 1) {
            d.push(x[i] - x[i-1]);
        }
    }
}

int main() {
#ifdef Wearry 
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d%d%d", &n, &t, &s);
    for(int i = 1; i <= n; ++i) scanf("%d", x + i);

    solve();

    reverse(x + 1, x + n + 1);
    for(int i = 1; i <= n; ++i) x[i] = -x[i];
    t = n - 1 - t;
    s = n - s + 1;

    solve();

    printf("%lld\n", ans == LLONG_MAX ? -1 : ans);

    return 0;
}
