#include <bits/stdc++.h>
using namespace std;

const int N = 5000;

int n;
bool a[N + 5], b[N + 5];
char s[N + 5], t[N + 5];

int main() {
  scanf("%d%s%s", &n, s, t);

  if (n <= 2) {
      printf("%d\n", (s[0] != t[0]) + (s[1] != t[1]));
      return 0;
  }

  for (int i = 1; i < n; ++i) {
    a[i] = s[i] != s[i-1];
    b[i] = t[i] != t[i-1];
  }

  int ans = 0x3f3f3f3f;
  bool flag = s[0] != t[0];

  for (int i = flag; i < n; i += 2) {
    int res = 0;
    vector<int> tmp;
    for (int j = n - 1; j > 0; --j) if(a[j] == 0) tmp.push_back(j);
    for (int j = 0; j < i; ++j) tmp.push_back(0);

    for (int j = 1; j < n; ++j) if(b[j] == 0) {
      if (tmp.size()) {
        res += abs(j - tmp.back());
        tmp.pop_back();
      } else {
        res += n - j;
      }
    }

    while(!tmp.empty()) {
      res += n - tmp.back();
      tmp.pop_back();
    }
    ans = min(ans, res);
  }
  
  swap(a, b);
  for (int i = flag; i < n; i += 2) {
    int res = 0;
    vector<int> tmp;
    for (int j = n - 1; j > 0; --j) if(a[j] == 0) tmp.push_back(j);
    for (int j = 0; j < i; ++j) tmp.push_back(0);

    for (int j = 1; j < n; ++j) if(b[j] == 0) {
      if (tmp.size()) {
        res += abs(j - tmp.back());
        tmp.pop_back();
      } else {
        res += n - j;
      }
    }

    while(!tmp.empty()) {
      res += n - tmp.back();
      tmp.pop_back();
    }
    ans = min(ans, res);
  }
  printf("%d\n", ans);
  return 0;
}
