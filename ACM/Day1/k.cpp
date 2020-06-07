#include <bits/stdc++.h>
using namespace std;

const int N = 3000000;

int n;
int fa[N + 5];

vector<int> bel[N + 5];
int sum[N + 5], flag[N + 5];

int findset(int x) {
    return (fa[x] == x) ? x : fa[x] = findset(fa[x]);
}

void fixed(int x) {
    x = findset(x);
    for (auto y : bel[x]) {
        flag[y >> 1] = true;
    }
}

void make(int x) {
    x = findset(x);
    for (auto y : bel[x]) {
        flag[y >> 1] = true;
        sum[y >> 1] = y & 1;
    }
}

void reverse(int x) {
    x = findset(x);
    for (auto y : bel[x]) {
        if (flag[y >> 1]) fail();
        flag[y >> 1] = true;
        sum[y >> 1] ^= 1;
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
#endif

    for (int i = 0; i < N; ++i) fa[i] = i;

    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);

        fa[findset(x << 1)] = findset(y << 1 | 1);
        fa[findset(x << 1 | 1)] = findset(y << 1);
    }

    for (int i = 1; i <= 2*n; ++i) {
        bel[findset(i << 1)].push_back(i << 1);
        bel[findset(i << 1 | 1)].push_back(i << 1 | 1);

        if (findset(i << 1) == findset(i << 1 | 1)) {
            fail();
        }
    }

    for (int i = 2*n; i >= 1; --i) {
        if (!flag[i]) make(i << 1);
    }

    memset(flag, 0, sizeof flag);

    fixed(n << 2);

    for (int i = 2*n; i >= 2; --i) {
        if (sum[i] == sum[i-1] && sum[i-1] == sum[i-2]) {
            reverse((i-2) << 1 | sum[i-2]);
        }
    }

    if (sum[1] == sum[0] && sum[2*n] == sum[2*n-1]) {
    }

    return 0;
}
