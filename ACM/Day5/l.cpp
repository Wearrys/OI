#include <bits/stdc++.h>
using namespace std;
int T;
long long a, b, k, c, ans;
map<pair<long long, long long>,int > anss;
int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
#endif
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld", &a, &b);
        if (anss.find(make_pair(a,b))!=anss.end())
        {
            printf("%d\n", anss[make_pair(a,b)]);
            continue;
        }
        long long ta=a,tb=b;
        ans = 0;
        if (a < 0) {
            a = -a;
            ans = (a - 1) / b + 1;
            a = -(a - ans * b);
            #ifdef _noname
			printf("ans=%lld,a=%lld,b=%lld\n", ans, a, b);
            #endif
        }
        if (a > b) {
            k = a / b;
            c = a % b;
            ans += 2 + (k - 1) * 3;
            b = b + c;
            a = c;
        }
        #ifdef _noname
        printf("ans=%lld,a=%lld,b=%lld\n", ans, a, b);
        #endif
        while (a != 0) {
            k = b / a;
            c = b % a;
            if (c == 0) {
                ans += k + 1;
                a = 0;
            } else if (k == 1) {
                ans += 1ll * (k + 2) * (a / c);
                a = a % c;
                b = a + c;
            } else {
                ans += k + 2;
                b = a;
                a -= c;
            }
            #ifdef _noname
			printf("ans=%lld,a=%lld,b=%lld\n", ans, a, b);
            #endif
        }
        anss[make_pair(ta,tb)]=ans%1000000007;
        printf("%lld\n", ans % 1000000007);
    }
    return 0;
}
