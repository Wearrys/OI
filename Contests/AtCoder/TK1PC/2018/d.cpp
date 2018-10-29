#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> ans[100000 + 5];

void solve(int k) {
    int cur = 1;
    puts("Yes");
    printf("%d\n", k);

    for(int i = 1; i <= k; ++i) {
        for(int j = i + 1; j <= k; ++j) {
            ans[i].push_back(cur);
            ans[j].push_back(cur ++);
        }
    }

    for(int i = 1; i <= k; ++i) {
        printf("%d ", (int) ans[i].size());
        for(auto v : ans[i]) printf("%d ", v);
        puts("");
    }
    exit(0);
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= 1000; ++i) {
        if(1ll * i * (i - 1) / 2 == n) {
            solve(i);
            break;
        }
    }
    return puts("No"), 0;
}
