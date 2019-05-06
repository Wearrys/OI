#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int mo = 1e9 + 7;

int w, b;
int fac[N + 5], inv[N + 5];
int pre[N + 5], suf[N + 5], ans[N + 5];

int fpm(int x, int y) {
  int res = 1;
  for (; y > 0; y >>= 1) {
    if (y & 1)
      res = 1ll * res * x % mo;
    x = 1ll * x * x % mo;
  }
  return res;
}

void init() {
  fac[0] = 1;
  for (int i = 1; i <= N; ++i) fac[i] = 1ll * fac[i-1] * i % mo;
  inv[N] = fpm(fac[N], mo - 2);
  for (int i = N; i >= 1; --i) inv[i-1] = 1ll * inv[i] * i % mo;
}

inline int binom(int x, int y) {
  if (x < 0 || y < 0 || x < y) return 0;
  return 1ll * fac[x] * inv[y] % mo * inv[x - y] % mo;
}

int main() {

  init();
  cin >> b >> w;

  for (int i = 1; i <= b; ++i) {
    int p = fpm(fpm(2, mo - 2), w + b - i);
    suf[w + b - i + 1] = (suf[w + b - i + 1] + 1ll * binom(w + b - i - 1, w - 1) * p) % mo;
    pre[w + b - i - 1] = (pre[w + b - i - 1] + 1ll * binom(w + b - i - 2, b - i - 1) * p) % mo;
  }

  for (int i = 1; i <= w; ++i) {
    int p = fpm(fpm(2, mo - 2), w + b - i);
    pre[w + b - i - 1] = (pre[w + b - i - 1] + 1ll * binom(w + b - i - 2, b - 2) * p) % mo;
    ans[w + b - i] = (ans[w + b - i] + 1ll * binom(w + b - i - 1, b - 1) * p) % mo;
  }

  for (int i = 1; i <= w + b; ++i) {
    suf[i] = (suf[i] + suf[i-1]) % mo;
    ans[i] = (ans[i] + suf[i]) % mo;
  }

  for (int i = w + b; i >= 1; --i) {
    pre[i] = (pre[i] + pre[i+1]) % mo;
    ans[i] = (ans[i] + pre[i]) % mo;
  }

  for (int i = 1; i <= w + b; ++i) {
    printf("%d\n", ans[i]);
  }

  return 0;
}
