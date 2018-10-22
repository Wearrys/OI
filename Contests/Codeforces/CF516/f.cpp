#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int B = 29;
const int N = 500000;

int n;
char st[N + 5];

ull hs[N + 5], pw[N + 5];
unordered_map <ull, int> lst;

ull get_hs(int l, int t) {
    int r = l + t - 1;
    return hs[r] - hs[l - 1] * pw[r - l + 1];
}

int find(int l, int r) {
    ull hs_v = get_hs(l, r);
    return !lst.count(hs_v) ? 0 : lst[hs_v];
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d%s", &n, st + 1);
    
    pw[0] = 1;
    hs[0] = 0;

    for(int i = 1; i <= n; ++i) {
        pw[i] = pw[i - 1] * B;
        hs[i] = hs[i - 1] * B + st[i] - 'a' + 1;
    }

    int len = 0, ans = 0;
    for(int i = n; i >= 1; --i) {
        ++ len;
        while(len > 1 && max(find(i, len - 1), find(i + 1, len - 1)) < i + len) -- len;

        ans = max(ans, len);
        for(int j = len; j > 0 && !lst.count(get_hs(i, j)); --j) {
            lst.insert(make_pair(get_hs(i, j), i));
        }
    }
    printf("%d\n", ans);

    return 0;
}
