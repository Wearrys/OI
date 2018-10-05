#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back
#define mp std::make_pair
#define debug(...) fprintf(stderr, __VA_ARGS__)

template <typename T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;

template <typename T> T read(T& x) {
    T f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = 200000;

int n, m;
char st[N + 5];
int ans[N + 5];
vector<int> a, b, c, d;

int main() {
#ifdef Wearry
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    scanf("%d%s", &n, st + 1), st[0] = st[n << 1] = '1';

    for(int i = 0; i < n << 1; ++i) {
        if(st[i] == '0' && st[i+1] == '0') {
            a.pb(i);
        } else if(st[i] == '0' && st[i+1] == '1') {
            b.pb(i);
        } else if(st[i] == '1' && st[i+1] == '0') {
            c.pb(i);
        } else {
            d.pb(i);
        }
    }

    int k = d.size();
    if(k & 1) return puts("No"), 0;
    if(k & 2) {
        int x = 0;
        for(; x < (n << 1) && st[x] == '1'; ++ x);
        if(x >= (n << 1)) return puts("No"), 0;

        while(true) {
            for(; x < (n << 1) && st[x] == '0'; ++ x);
            if(x >= (n << 1)) return puts("No"), 0;

            if(st[x + 1] == '1') {
                break;
            } else {
                x += 2;
            }
        }

        int y = x + 1, z = 0;
        for(; y < (n << 1) && st[y] == '1'; ++ y);
        if(y >= (n << 1)) return puts("No"), 0;

        for(; z < k && d[z] > x-1 && d[z] < y-1; ++ z);
        if(z >= k) return puts("No"), 0;

        for(; z+1 < k && d[z+1] < x-1; ++ z);

        int o = x - 1, p = y - 1;
        ans[o] = ans[p] = ++ m; 
        b.erase(std::lower_bound(b.begin(), b.end(), o)); 
        c.erase(std::lower_bound(c.begin(), c.end(), p));

        int q = x, r = d[z];
        ans[q] = ans[r] = ++ m;
        d.erase(std::lower_bound(d.begin(), d.end(), q)); 
        d.erase(std::lower_bound(d.begin(), d.end(), r));
    }

    for(int i = 0; i < (int) a.size(); i += 2) {
        ans[a[i]] = ans[a[i+1]] = ++ m;
    }
    for(int i = 0; i < (int) b.size(); ++i) {
        ans[c[i]] = ans[b[i]] = ++ m;
    }
    for(int i = 0; i < (int) d.size(); i += 4) {
        ans[d[i]] = ans[d[i + 2]] = ++ m;
        ans[d[i + 1]] = ans[d[i + 3]] = ++ m;
    }

    puts("Yes");
    for(int i = 0; i < (n << 1); ++i) {
        printf("%d ", ans[i]);
    }
    puts("");

    return 0;
}
