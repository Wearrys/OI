#include <bits/stdc++.h>
using namespace std;

namespace LIB {
    const int N=30;
    int dim[N],dimcnt;

    template <typename T> 
    void dfs(int dep, T g, int x, int y, int z, int n) {
        if(dep > dimcnt) {
            g[x-1][y-1] = z-1;
            return;
        }

        int d = n / dim[dep];
        for(int i = 0; i < n; i += d) 
            for(int j = 0; j < n; j += d) 
                dfs(dep + 1, g, x + i, y + j, z + (i + j) % n, d);
    }

    template <typename T1, typename T2>
    inline int put_reaction(int t, T1 a, T2 g) {
        int n = 1;
        dimcnt = t;
        for(int i = 1; i <= t; ++i) n *= dim[i] = a[i];
        dfs(1, g, 1, 1, 1, n);
        return n;
    }
}

const int N = 3000;

int t, m, q;
int a[N + 5], b[N + 5][N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d%d%d", &t, &m, &q);
    for(int i = 1; i <= t; ++i) scanf("%d", a + i);
    int n = LIB::put_reaction(t, a, b);

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            printf("%d ", b[i][j]);
        } puts("");
    }

    return 0;
}
