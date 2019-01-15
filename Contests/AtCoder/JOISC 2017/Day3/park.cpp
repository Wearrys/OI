#include "park.h"

const int MAXN = 1400 + 5;

int n;
int P[MAXN];
bool vis[MAXN];
int bfn[MAXN], bfs_seq[MAXN];

void solve(int x) {

}

void Detect(int T, int N) {
    n = N;
    vis[0] = true;

    for(int i = 1; i < n; ++i) if(!vis[i]) {
        solve(i);
    }
}
