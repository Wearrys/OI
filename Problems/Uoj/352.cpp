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

string procStatus() {
    std::ifstream t("/proc/self/status");
    return string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}

template <typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = 10;

int n;
int a[N + 5][N + 5];
int l[N + 5], r[N + 5], x[N + 5], y[N + 5];

double calc() {
    int tot = 0, ans = 0;

    vector<int> v1;
    for(int i = 0; i < n; ++i) if(l[i] ^ r[i]) v1.pb(i);

    do {
        ++ tot;
        bool flag = true;

        for(int i = 0; i < (int) v1.size(); ++i) y[v1[i]] = i;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(i == j) {
                    flag &= (a[i][j] <= 0);
                    continue;
                }

                if(l[j] == r[j]) {
                    flag &= (x[i] - x[j] >= a[i][j]);
                } else if(l[i] == r[i]) {
                    flag &= (x[i] - x[j] >= a[i][j] + 1);
                } else {
                    int val = a[i][j] - x[i] + x[j];

                    if(val >= 1) flag = false;
                    if(val == 0) flag &= (y[i] > y[j]);
                }

                if(!flag) break;
            }
            if(!flag) break;
        }

        ans += flag;
    } while (next_permutation(v1.begin(), v1.end()));

    return 1. * ans / tot;
}

int tot;
double ans;

void dfs(int cur) {
    if(cur == n) {
        ++ tot;
        ans += calc();
        return;
    }

    if(l[cur] == r[cur]) {
        x[cur] = l[cur];
        dfs(cur + 1);
    } else {
        for(int i = l[cur]; i < r[cur]; ++i) {
            x[cur] = i;
            dfs(cur + 1);
        }
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    for(int i = 0; i < n; ++i) read(l[i]), read(r[i]);
    for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) read(a[i][j]);

    dfs(0);
    printf("%.10lf\n", ans / tot);

    return 0;
}
