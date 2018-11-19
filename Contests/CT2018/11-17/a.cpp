#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;

int n, q;
int a[N + 5], c[N + 5];

#define lowbit(x) (x & -x)

void add(int x, int y) {
    while(x <= N) {
        c[x] ^= y;
        x += lowbit(x);
    }
}

int query(int x) {
    int res = 0;
    while(x > 0) {
        res ^= c[x];
        x -= lowbit(x);
    }
    return res;
}

int ans[N + 5], s[N + 5];
unordered_map <int, int> lst;
vector <pair<int, int> > que[N + 5];

int main() {

    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; ++i) scanf("%d", a + i), s[i] = s[i-1] ^ a[i];
    for(int i = 1; i <= q; ++i) {
        static int x, y; 
        scanf("%d%d", &x, &y);
        que[y].push_back(make_pair(x, i));
    }

    for(int i = 1; i <= n; ++i) {
        if(lst[a[i]]) 
            add(lst[a[i]], a[i]);
        add(lst[a[i]] = i, a[i]);

        for(auto t : que[i]) {
            ans[t.second] = s[i] ^ s[t.first-1] ^ query(i) ^ query(t.first-1);
        }
    }

    for(int i = 1; i <= q; ++i) {
        printf("%d\n", ans[i]);
    }

    return 0;
}
