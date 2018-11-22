#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned int uint;

template <typename T> inline bool chkmin(T& a, T b) {
    return a < b ? 0 : a = b, 1;
}

template <typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

namespace DAG {

    const int N = 20;

    int ind[N + 5];
    vector<int> G[N + 5];

    inline void addedge(int x, int y) {
        ++ ind[y];
        G[x].push_back(y);
    }

    int bel[N + 5], m;
    int low[N + 5], dfn[N + 5], dfc;

    void dfs(int x) {
        static int stk[N + 5], top;

        stk[top ++] = x;
        low[x] = dfn[x] = ++ dfc;   

        for(auto y : G[x]) {
            if(!dfn[y]) {
                dfs(y);
                chkmin(low[x], low[y]);
            } else if(!~bel[y]) {
                chkmin(low[x], dfn[y]);
            }
        }

        if(low[x] >= dfn[x]) {
            do {
                bel[stk[top - 1]] = m;
            } while(top > 0 && stk[-- top] != x);
            ++ m;
        }
    }

    int es[N + 5];
    uint coe[N + 5];
    uint f[(1 << N) + 5];
    uint gcd[N + 5][N + 5];
    uint bin[N + 5][N + 5];

    void prework() {
        for(int i = 0; i <= m; ++i) {
            for(int j = 0; j <= m; ++j) {
                if(!i || !j) gcd[i][j] = i + j;
                else gcd[i][j] = gcd[j % i][i];
            }
        }

        for(int i = 0; i <= m; ++i) {
            bin[i][0] = bin[i][i] = 1;
            for(int j = 1; j < i; ++j) {
                bin[i][j] = bin[i-1][j-1] + bin[i-1][j];
            }
        }
    }

    void init(int n) {
        for(int i = 1; i <= n; ++i) bel[i] = -1;
        for(int i = 1; i <= n; ++i) if(!dfn[i]) dfs(i);
        for(int i = 1; i <= n; ++i) bel[i] = m - 1 - bel[i];
        for(int i = 1; i <= n; ++i)
            for(int j : G[i]) if(bel[i] != bel[j]) es[bel[j]] |= (1 << bel[i]);

        f[0] = 1;
        for(int i = 1; i <= m; ++i) {
            for(int j = 0; j < m; ++j) {
                for(int s = 0; s < (1 << m); ++s) {
                    if((es[j] & s) == es[j] && ((s >> j & 1) ^ 1)) f[s | (1 << j)] += f[s];
                }
            }
            coe[i] = f[(1 << m) - 1];
        }

        prework();

        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j < i; ++j) {
                coe[i] -= coe[j] * bin[i][j];
            }
        }
    }

    uint calc(ll x) {
        uint res = 0;
        static ll d[N + 5];

        for(uint i = 1; i <= m && i <= x; ++i) {
            uint t = i, binom = 1;

            d[i] = x - i + 1;
            for(int j = 1; t > 1; ++j) {
                uint r = gcd[d[j] % t][t];
                d[j] /= r, t /= r;
            }

            for(uint j = 1; j <= i; ++j) binom *= d[j];
            res += binom * coe[i];
        }
		return res;
	}
}

namespace SIV {

    const int M = 100000;

    ll n;
    int m;
    uint val[M + 5];
    int prime[M + 5], pcnt;
    uint s[M + 5], S[M + 5];
    uint f[M + 5], F[M + 5];

    inline uint gets(ll x) { return x <= m ? s[x] : S[n / x]; }
    inline uint getf(ll x) { return x <= m ? f[x] : F[n / x]; }

    int my_sqrt(ll x) {
        int r = 1;
        while(1ll * (r + 1) * (r + 1) <= x) ++ r;
        return r;
    }

    void init(ll _n) {
        m = my_sqrt(n = _n);
       
        for(int i = 1; i <= m; ++i) {
            val[i] = 81 * i * i - 27 * i + 9;
            s[i] = i - 1;
            S[i] = (n / i) - 1;
        }

        for(int p = 2; p <= m; ++p) {
            if(s[p] == s[p-1]) continue;
            prime[pcnt ++] = p;
             
            const uint _s = s[p - 1];
            const ll q = 1ll * p * p, lim = min((ll) m, n / q), x = m / p, y = n / p;

            for(int i = 1; i <= x; ++i) S[i] -= S[i * p] - _s;
            for(int i = x + 1; i <= lim; ++i) S[i] -= s[y / i] - _s;
            for(int i = m; i >= q; --i) s[i] -= s[i / p] - _s;
        }

        for(int i = 1; i <= m; ++i) {
            f[i] = s[i] * 63;
            F[i] = S[i] * 63;
        }

        for(int e = pcnt; e >= 1; --e) {
            int p = prime[e-1];
            const ll q = 1ll * p * p, lim = min((ll) m, n / q);

            for(int i = 1; i <= lim; ++i) {
                ll cur = n / i;
                for(ll t = p, c = 1; t * p <= cur; t *= p, ++ c) {
                    F[i] += (getf(cur / t) - e * 63) * val[c] + val[c + 1];
                }
            }

            for(int i = m; i >= q; --i) {
                int cur = i;
                for(int t = p, c = 1; t <= cur / p; t *= p, ++ c) {
                    f[i] += (getf(cur / t) - e * 63) * val[c] + val[c + 1];
                }
            }
        }
    }
}

ll m;
int n, k;

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n), read(m), read(k);
    for(int i = 1; i <= k; ++i) {
        static int x, y;
        read(x), read(y);
        DAG::addedge(x, y);
    }

    DAG::init(n);
    SIV::init(m);

    uint res = 0, cur, lst = -1;
    for(ll i = 1, nxt; i <= m; i = nxt + 1) {
        nxt = m / (m / i), cur = SIV::getf(nxt);
        res += DAG::calc(m / i) * (cur - lst), lst = cur;
    }
    printf("%u\n", res);

    return 0;
}
