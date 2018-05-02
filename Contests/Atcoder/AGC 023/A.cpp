#include <map>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200000;

typedef long long ll;

ll s, ans;
int n, a;
map<ll, int> mp;

int main() {
#ifdef Wearry 
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d", &n);

    mp[0] = 1;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a);
        s += a;
        ans = (ans + mp[s]);

        if(!mp.count(s)) {
            mp[s] = 1;
        } else mp[s] ++;
    }
    printf("%lld\n", ans);

    return 0;
}
