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

const int N = 200000;

int n, q;
int a[N + 5];
int s[2][N + 5];

bool flag;
std::set<int> S;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    S.insert(0);
    read(n), read(q);
    for(int i = 1; i <= n; ++i) s[0][read(a[i])] ++;

    if(!s[0][q]) flag = true;
    for(int i = 1; i <= n; ++i) {
        if(a[i]) {
            if(!-- s[0][a[i]]) S.erase(a[i]);
            if(a[i] < (*S.rbegin())) return puts("NO"), 0;
            if(s[0][a[i]] && !s[1][a[i]] ++) S.insert(a[i]);
        } else {
            a[i] = (*S.rbegin());
            if(!a[i]) a[i] = 1;
            if(flag) a[i] = q, flag = false;
            if(s[0][a[i]] && !s[1][a[i]] ++) S.insert(a[i]);
        }
    }
    if(flag) return puts("NO"), 0;
    puts("YES");
    for(int i = 1; i <= n; ++i) printf("%d ", a[i]);

    return 0;
}
