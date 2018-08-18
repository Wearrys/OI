#include <bits/stdc++.h>

using std::pair;
using std::vector;
using std::string;

#define fst first
#define snd second
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)

template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;

template<typename T> T read(T& x) {
    T f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}
const int N = 10000;

int n;
struct stu {
    int sum, id;
    bool operator < (const stu& rhs) const {
        return sum > rhs.sum || (sum == rhs.sum && id < rhs.id);
    }
};

stu s[N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    for(int i = 1; i <= n; ++i) {
        static int a, b, c, d;
        s[i].sum += read(a) + read(b) + read(c) + read(d);
        s[i].id = i;
    }
    std::sort(s + 1, s + n + 1);
    for(int i = 1; i <= n; ++i) if(s[i].id == 1) printf("%d\n", i);

    return 0;
}
