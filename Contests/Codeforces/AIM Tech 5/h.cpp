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

const int N = 200000;
const int M = 5100000;

int n, q;
int a[N + 5];
int p[M + 5], rng[N + 5][13], L[13];

vector <int> vec;
int pos[M + 5][13];

void dfs(int cur, int id, int mul, int cnt = 0) {
    if(cur == (int) vec.size()) {
        for(int i = 0; i + cnt < 13; ++i) chkmax(L[i + cnt], pos[mul][i]);
        pos[mul][cnt] = id;
        return;
    } 

    dfs(cur + 1, id, mul, cnt + 1);
    dfs(cur + 1, id, mul * vec[cur], cnt);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    
    read(n), read(q);
    for(int i = 1; i <= n; ++i) read(a[i]);
    for(int i = 2; i <= M; ++i) if(!p[i]) {
        for(int j = i + i; j <= M; j += i) p[j] = i;
    }

    for(int i = 1; i <= n; ++i) {
        vec.clear();

        int x = a[i];
        while(p[x]) {
            int y = p[x], c = 0;
            while(x % y == 0) x /= y, c ^= 1;
            if(c) vec.pb(y);
        }
        if(x > 1) vec.pb(x);

        dfs(0, i, 1);
        for(int j = 0; j < 13; ++j) rng[i][j] = L[j];
    }

    while(q--) {
        static int l, r, ans;
        read(l), read(r);

        ans = 0;
        while(rng[r][ans] < l) ++ ans;
        printf("%d\n", ans);
    }

    return 0;
}
