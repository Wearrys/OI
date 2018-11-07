#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;

int n, c, m;
int x[N + 5], y[N + 5];

int main() {
    scanf("%d", &n);

    if(n % 5 == 0 || (n % 5 >= 3)) {
        int k = (n - 1) / 5;
        for(int i = 1; i <= 2*k + 1; ++i) x[i] = i;
        for(int i = 4*k + 1; i >= 2*k + 3; i -= 2) y[++ c] = i;
        for(int i = 4*k + 2; i >= 2*k + 2; i -= 2) y[++ c] = i;
    } else {
        int k = n / 5;
        for(int i = 1; i <= 2*k; ++i) x[i] = i;
        for(int i = 4*k-1; i >= 2*k+1; i -= 2) y[++ c] = i;
        for(int i = 4*k; i >= 2*k+2; i -= 2) y[++ c] = i;
    }

    printf("%d\n", c);
    for(int i = 1; i <= c; ++i) {
        printf("%d %d\n", x[i], y[i]);
    }
    return 0;
}
