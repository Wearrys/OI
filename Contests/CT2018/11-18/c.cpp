#include <bits/stdc++.h>
using namespace std;

const int K = 150;
const int mo = 998244353;

int k;

struct mat_t {
    int v[K + 5][K + 5];

    mat_t(bool t = 0) {
        for(int i = 0; i <= k; ++i) {
            for(int j = 0; j <= k; ++j) {
                v[i][j] = ((i == j) && t);
            }
        }
    }
};

mat_t operator * (const mat_t &a, const mat_t & b) {
    mat_t c;
    for(int i = 0; i <= k; ++i) {
        for(int j = 0; j <= k; ++j) {
            for(int l = 0; l <= k; ++l) {
                c.v[i][l] = (c.v[i][l] + 1ll * a.v[i][j] * b.v[j][l]) % mo;
            }
        }
    }
    return c;
}

long long n;
vector<int> digit;

mat_t dp[60][8];

mat_t trans(int s) {
    mat_t t(1);
    for(int i = 0; i <= k; ++i) {
        t.v[s][i] = 1;
    }
    return t;
}

mat_t shift(const mat_t& a, int b) {
    mat_t c;
    for(int i = 0; i < k; ++i) {
        for(int j = 0; j < k; ++j) {
            c.v[(i + b) % k][(j + b) % k] = a.v[i][j];
        }
    }
    for(int i = 0; i < k; ++i) c.v[(i + b) % k][k] = a.v[i][k];
    for(int i = 0; i <= k; ++i) c.v[k][i] = a.v[k][i];
    return c;
}

mat_t get_pre(int u, int l, int r) {
    mat_t res = 1;
    int b = r - l + 1, s = 0;

    for(int i = 0; i < 8; ++i) if(b >> i & 1) {
        res = res * shift(dp[u][i], s);
        s |= 1 << i;
    }
    return shift(res, l);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
#endif

    scanf("%lld%d", &n, &k);
    while(n > 0) digit.push_back(n % k), n /= k;

    dp[0][0] = trans(0);
    for(int i = 1; i < 8; ++i) {
        dp[0][i] = dp[0][i-1] * shift(dp[0][i-1], 1 << (i-1));
    }

    for(int i = 0; i < (int) digit.size(); ++i) {
        dp[i+1][0] = get_pre(i, 0, k-1);
        for(int j = 1; j < 8; ++j) {
            dp[i+1][j] = dp[i+1][j-1] * shift(dp[i+1][j-1], 1 << (j-1));
        }
    }

    int s = 0;
    mat_t x = 1;

    for(int i = (int) digit.size() - 1; i >= 0; --i) {
        if(digit[i]) {
            int l = s, r = (s + digit[i] - 1) % k;
            if(r < l) {
                x = x * get_pre(i, l, k-1) * get_pre(i, 0, r);
            } else {
                x = x * get_pre(i, l, r);
            }
        }
        (s += digit[i]) %= k; 
    }

    int ans = 0;
    for(int i = 0; i <= k; ++i) {
        ans = (ans + x.v[i][k]) % mo;
    }
    printf("%d\n", ans);

    return 0; 
}
