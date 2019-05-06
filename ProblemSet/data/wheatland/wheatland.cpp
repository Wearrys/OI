#include <bits/stdc++.h>
using namespace std;

const int N = 200;

int n, m, k;
char st[N + 5][N + 5];
int dis[2*N + 5][N + 5][N + 5];

struct node {
  int d, x, y;
};

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%s", st[i]);
  }
  k = min(k, n + m);

  queue<node> que;
  memset(dis, 0x3f, sizeof dis);

  dis[st[0][0] == '1'][0][0] = 0;
  que.push((node) { st[0][0] == '1', 0, 0 });

  const int dx[] = { 0, 1, 0, -1 };
  const int dy[] = { 1, 0, -1, 0 };

  while (!que.empty()) {
    node x = que.front(); que.pop();

    for (int d = 0; d < 4; ++d) {
      int nx = x.x + dx[d];
      int ny = x.y + dy[d];
      int nd = x.d + (st[nx][ny] == '1');

      if (nd > k || nx < 0 || nx >= n || ny < 0 || ny >= m) {
        continue;
      }

      if (dis[nd][nx][ny] > dis[x.d][x.x][x.y] + 1) {
        dis[nd][nx][ny] = dis[x.d][x.x][x.y] + 1;
        que.push((node) { nd, nx, ny });
      }
    }
  }

  int ans = 1e9;
  for (int d = 0; d <= k; ++d) {
    ans = min(ans, dis[d][n-1][m-1]);
  }

  if (ans == 1e9) {
    printf("no solution\n");
  } else {
    printf("%d\n", ans);
  }

  return 0;
}
