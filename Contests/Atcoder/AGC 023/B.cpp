#include <cstdio>
#include <bitset>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 300;

int n;
char st[N + 5][N + 5];

bitset<2*N + 5> b[N + 5][N + 5];

int main() {
#ifdef Wearry 
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    scanf("%d", &n);
    for(int i = 0; i < n; ++i) { scanf("%s", st[i]); }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            int d = (i - j + n) % n;
            for(int k = 0; k < n; ++k) {
                if(st[i][k] == st[j][(k + d) % n]) b[i][j][k] = b[i][j][k + n] = 1;
            }
        }
    }

    int ans = 0;
    for(int a = 0; a < n; ++a) {

        bitset<2*N + 5> res;
        for(int i = 0; i < n; ++i) res[i] = 1;

        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                int x = (i + a) % n, y = (j + a) % n;
                res = (res & (b[x][y] >> j));
            }
        }
        ans = (ans + res.count());
    }
    printf("%d\n", ans);

    return 0;
}
