#include <bits/stdc++.h>
#include <tr1/unordered_map>

using std::pair;
using std::vector;
using std::string;

typedef long long ll;
typedef pair<ll, ll> pll;
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

int lim[2], n, m;
vector<pll> G[N + 5];
ll a[N + 5], b[N + 5], c[N + 5];

inline bool chk(ll ans) {
    for(int p = 0; p < 2; ++p) {
        int k = lim[p];
        if(a[k] < ans) return true;

        for(int d = 0; d < 2; ++d) {
            ll t = a[k] - (ans - d);
            
            for(int i = 0; i <= n; ++i) b[i] = c[i] = 0;
            for(int i = 1; i <= n; ++i) {
                for(int j = 0; j < (int) G[i].size(); ++j) {
                    if(i <= k && G[i][j].fst > k) { 
                        continue; 
                    }

                    b[i] += G[i][j].snd;
                    b[G[i][j].fst] -= G[i][j].snd;
                }
                b[i] += b[i-1];
            }
            
            bool flag = true;
            static pll que[N + 5];
            ll reved = 0, tot = 0, sum = 0;

            for(int i = 1; i <= k; ++i) {
                for(int j = 0; j < (int) G[i].size(); ++j) {
                    if(G[i][j].fst > k) {
                        sum += G[i][j].snd;
                        que[tot ++] = G[i][j];
                        std::push_heap(que, que + tot);
                    }
                }

                ll cur = (b[i] + sum + t - reved - ans + 1) / 2;
                chkmax(cur, 0ll);

                if(sum < cur || reved + cur > t) {
                    flag = false;
                    break;
                } else {
                    reved += cur;
                    while(cur && cur >= que[0].snd) {
                        sum -= que[0].snd;
                        cur -= que[0].snd;
                        c[que[0].fst] += que[0].snd;
                        std::pop_heap(que, que + (tot --));
                    }
                    if(cur) {
                        sum -= cur;
                        que[0].snd -= cur; 
                        c[que[0].fst] += cur;
                    }
                }
            }

            for(int i = 0; i < tot; ++i) {
                c[k] += que[i].snd;
                c[que[i].fst] -= que[i].snd;
            }
            for(int i = k + 1; i <= n; ++i) {
                c[i] += c[i-1];
                if(b[i] + c[i] > ans) { flag = false; break; }
            }

            if(flag) return true;
        }
    }
    return false;
}

ll ans = 0;
int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n); read(m);
    for(int i = 1; i <= m; ++i) {
        static int l, r, t; 
        read(l), read(r), read(t);
        if(l > r) std::swap(l, r);

        a[l] += t, a[r] -= t, G[l].pb(mp(r, t));
    }

    ll mx = 0;
    lim[0] = oo, lim[1] = -oo;

    for(int i = 1; i <= n; ++i) { chkmax(mx, a[i] += a[i-1]); }
    for(int i = 1; i <= n; ++i) { 
        if(a[i] == mx) {
            chkmin(lim[0], i);
            chkmax(lim[1], i);
        }
    }

    ll L = 0, R = mx;
    while(L < R) {
        ll M = (L + R) >> 1;
        if(chk(M)) R = M; else L = M + 1;
    }
    printf("%lld\n", L);

    return 0;
}
