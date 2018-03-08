#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
typedef pair<int, int> pii;
 
#define fst first
#define snd second
#define pb push_back
#define eb emplace_back
#define REP(i, a, b)  for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i=(a-1), i##end = (b); i >=i##end; --i)
 
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
 
const LL oo = 2e12 + 5;
const int maxn = 1000000 + 5;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int n, m, k;
LL now[maxn];
LL pre[maxn], suf[maxn];
vector<pii> in[maxn], out[maxn];

int main() {
#ifdef Wearry
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= m; ++i) {
        static int d, s, t, c;
        d = read<int>();
        s = read<int>();
        t = read<int>();
        c = read<int>();

        if(s == 0) out[d].pb(pii(t, c));
        if(t == 0) in[d].pb(pii(s, c));
    }

    for(int i = 1; i <= n; ++i) now[i] = oo;

    pre[0] = 1LL * oo * n;
    for(int i = 1; i <= int(1e6); ++i) {
        pre[i] = pre[i-1];
        if(in[i].size()) {
            for(int j = 0; j < int(in[i].size()); ++j) {
                pre[i] -= now[in[i][j].fst];
                chkmin(now[in[i][j].fst], 1LL * in[i][j].snd);
                pre[i] += now[in[i][j].fst];
            }
        }
    }

    for(int i = 1; i <= n; ++i) now[i] = oo;

    suf[1000001] = 1LL * oo * n;
    for(int i = int(1e6); i >= 1; --i) {
        suf[i] = suf[i+1];
        if(out[i].size()) {
            for(int j = 0; j < int(out[i].size()); ++j) {
                suf[i] -= now[out[i][j].fst];
                chkmin(now[out[i][j].fst], 1LL * out[i][j].snd);
                suf[i] += now[out[i][j].fst];
            }
        }
    }

    LL res = LLONG_MAX;
    for(int i = 1; i+k+1 <= int(1e6); ++i) {
        chkmin(res, pre[i] + suf[i+k + 1]);
    }
    printf("%I64d\n", res < oo ? res : -1);

    return 0;
}
