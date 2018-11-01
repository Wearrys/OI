#include <bits/stdc++.h>
using namespace std;

int n;
int main() {
    scanf("%d", &n);

    int x = n / 3;
    for(int i = 1; i <= x; ++i) {
        printf("1 %d\n", 2*i);
    }
    for(int i = 1; i <= n-x; ++i) {
        printf("4 %d\n", i);
    }

    return 0;
}
