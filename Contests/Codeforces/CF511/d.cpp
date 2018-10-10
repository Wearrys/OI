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

const int N = 300000;

int n, k;
int L[N + 5], R[N + 5];

struct node {
    int l, r, v;

    bool operator < (const node& rhs) const {
        return l < rhs.l;
    }
};

std::set<node> S;
std::set<node> :: iterator it;

vector<pii> diff[N + 5];

void insert(int x, int y, int t) {
    it = -- S.lower_bound((node) { x, y, t });
    if(it -> r > x) {
        node temp = *it; S.erase(it);
        S.insert((node) { temp.l, x, temp.v });
        S.insert((node) { x, temp.r, temp.v });
    }
    it = -- S.lower_bound((node) { y, x, t });
    if(it -> r > y) {
        node temp = *it; S.erase(it);
        S.insert((node) { temp.l, y, temp.v });
        S.insert((node) { y, temp.r, temp.v });
    }

    it = S.lower_bound((node) { x, y, t });
    for(; it != S.end() && it -> r <= y; ) {
        diff[t].pb(mp(it -> v + 1, it -> r - it -> l)); 
        S.erase(it ++);
    }
    S.insert((node) { x, y, t });
}

ll ans;
int add[N + 5];

bool chk(int mid) {
    ll cnt = ans = 0;
    int sum = 0, ptr = 0;

    for(int i = 1; i <= n; ++i) add[i] = 0;
    for(int i = 1; i <= n; ++i) {
        for(auto v : diff[i]) {
            add[i + 1] -= v.snd;
            add[v.fst] += v.snd;

            if(i < ptr) {
                ans += (ll) (i - v.fst + 1) * v.snd * (n - i + 1);
            } else if(v.fst <= ptr) {
                sum += v.snd;
                ans += (ll) (ptr - v.fst + 1) * v.snd * (n - i + 1);
            }
        }
        for(; ptr < i && sum + add[ptr + 1] >= mid; ++ ptr) {
            sum += add[ptr + 1];
            cnt += (n - i + 1), ans += (ll) sum * (n - i + 1);
        }
    }

    if(cnt >= k) {
        ans -= (ll) (cnt - k) * mid;
        return true;
    } 
    return false;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(k);
    S.insert((node) { 0, (int) 1e9, 0 });
    for(int i = 1; i <= n; ++i) {
        read(L[i]), read(R[i]);
        insert(L[i], R[i], i);
    }

    int l = 1, r = 1e9;
    while(l < r) {
        int m = (l + r + 1) >> 1;
        if(chk(m)) l = m; else r = m - 1;
    }
    chk(l);
    printf("%lld\n", ans);

    return 0;
}
