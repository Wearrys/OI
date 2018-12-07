#include <bits/stdc++.h>
 
using std::pair;
using std::vector;
using std::string;

typedef long long ll;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb(a) push_back(a)
#define mp(a, b) std::make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const int oo = 0x3f3f3f3f;
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

const int K = 2000;

int n, k, ans;
int cnt[K + 5][K + 5];
int sa[K + 5], sb[K + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif 

    read(n); read(k);
    for(int i = 1; i <= n; ++i) {
        int x, y;
        char col[5];

        read(x), read(y); scanf("%s", col);

        if(((x/k + y/k)&1) ^ (col[0] == 'W')) {
            ++ sa[x % k];
            ++ sb[y % k];
            ++ cnt[x % k][y % k];
        } else {
            ++ ans;

            -- sa[x % k];
            -- sb[y % k];
            -- cnt[x % k][y % k];
        }
    }

    for(int i = 0; i <= k; ++i) {
        if(i > 0) sa[i] += sa[i-1];
        if(i > 0) sb[i] += sb[i-1];

        for(int j = 0; j <= k; ++j) if(j > 0) cnt[i][j] += cnt[i][j-1];
        for(int j = 0; j <= k; ++j) if(i > 0) cnt[i][j] += cnt[i-1][j];
    }

    int res = ans;
    for(int A = 0; A < k; ++A) {
        for(int B = 0; B < k; ++B) {
            chkmax(res, ans + sa[A] + sb[B] - 2*cnt[A][B]);
            chkmax(res, n - (ans + sa[A] + sb[B] - 2*cnt[A][B]));
        }
    }
    printf("%d\n", res);

    return 0;
}
