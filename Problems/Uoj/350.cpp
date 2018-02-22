#include <bits/stdc++.h>
using namespace std;

void out(long long x) {
    if(!x) return;
    out(x / 2);
    printf("%lld", x & 1ll);
}

int t;
long long n;

int main() {

    long long ed = (1e18);

    scanf("%d", &t);

    while(t--) {
        scanf("%lld", &n);

        if(n & 1) {
            if(n == 1) {
                printf("%d %d\n", 2, 3);
            } else if(n == 3) {
                printf("%d %d\n", 1, 2);
            } else {
                printf("%lld %lld\n", n - 3, n - 1);
            }
        } else {
            if(n + 3 > ed) {
                printf("%lld %lld\n", n - 4, n);
            } else {
                printf("%lld %lld\n", n + 1, n + 3);
            }
        }
    }
    
    return 0;
}
