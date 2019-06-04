#include <bits/stdc++.h>
using namespace std;

const int N = 300;
const int mo = 1e9 + 7;

int fac[2*N + 5], inv[2*N + 5];

int fpm(int x, int y) {
  int res = 1;
  while (y > 0) {
    if (y & 1) {
      res = 1ll * res * x % mo;
    }
    x = 1ll * x * x % mo;
    y >>= 1;
  }
  return res;
}

void init() {
  fac[0] = 1;
  for (int i = 1; i <= 2*N; ++i) fac[i] = 1ll * fac[i-1] * i % mo;
}

int n, x;
int a[2*N + 5], b[2*N + 5];
int f[2*N + 5][2*N + 5][2*N + 5];

int main() {

  init();
  scanf("%d", &n);

  memset(b, -1, sizeof b);
  for (int i = 0; i < 2*n; ++i) scanf("%d", a + i), b[a[i]] = i;
  for (int i = 0; i < 2*n; i += 2) x += (a[i] == -1) && (a[i + 1] == -1); 

  f[1][0][0] = 1;

  for (int i = 1; i <= 2*n; ++i) {
    for (int j = 0; j <= 2*n; ++j) {
      for (int k = 0; k <= 2*n; ++k) if (f[i][j][k]) {
        if (b[i] == -1) {
          f[i + 1][j + 1][k] = (f[i + 1][j + 1][k] + f[i][j][k]) % mo;
          f[i + 1][j][k + 1] = (f[i + 1][j][k + 1] + f[i][j][k]) % mo;
          if (k) f[i + 1][j][k - 1] = (f[i + 1][j][k - 1] + f[i][j][k]) % mo;
        } else if (a[b[i] ^ 1] == -1) {
          f[i + 1][j][k + 1] = (f[i + 1][j][k + 1] + f[i][j][k]) % mo;
          if (j) f[i + 1][j - 1][k] = (f[i + 1][j - 1][k] + 1ll * f[i][j][k] * j) % mo;
        } else {
          f[i + 1][j][k] = f[i][j][k];
        }
      }
    }
  }

  int ans = 1ll * fac[x] * f[2*n+1][0][0] % mo;
  printf("%d\n", ans);

  return 0;
}
