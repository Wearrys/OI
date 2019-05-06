#include <bits/stdc++.h>
using namespace std;

const int N = 10000000;

int l, r, p;
int val[N + 5];
bool notprime[N + 5];
int prime[N + 5], pcnt;

int main() {
  scanf("%d%d%d", &l, &r, &p);
  
  int ans = 0;
  for (int i = 2; i <= r; ++i) {
    if (!notprime[i]) {
      val[i] = 1;
      prime[pcnt ++] = i;
    }

    for (int j = 0; j < pcnt && i * prime[j] <= N; ++j) {
      notprime[i * prime[j]] = true;

      if (i % prime[j] == 0) {
        val[i * prime[j]] = val[i];
        break;
      }
      val[i * prime[j]] = val[i] + 1;
    }

    ans = (ans + 1ll * val[i] * (r / i - (l - 1) / i)) % p;
  }

  printf("%d\n", ans);
  return 0;
}
