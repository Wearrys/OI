#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 200000;

int n, q;
deque <int> ans;
int a[N + 5], s[N + 5];

int main() {

    scanf("%d", &n);
    for(int i = 0; i <= 1000000; ++i) ans.push_back(i);
    for(int i = 1; i < n; ++i) {
        scanf("%d", a + i), s[i] = s[i-1] + a[i];

        for(int j = 1; j <= a[i]; ++j) {
            ans.push_front(ans[(j << 1) - 1]);
        }
    }

    scanf("%d", &q);
    while(q--) {
        scanf("%d", a + n);

        if(a[n] > s[n-1]) {
            printf("%d ", a[n] - s[n-1]);
            continue;
        }

        printf("%d ", ans[a[n]]);
    }

    return 0;
}
