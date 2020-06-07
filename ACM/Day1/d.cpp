#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int N = 10000;
const int K = 4700;
const ull B = 4362109057;

char str[N];

ull mul(ull a, ull b) {
    ull res = 0;
    for (int i = 0; i < 32; ++i) if (a >> i & 1) {
        res ^= b << i;
    }
    for (int i = 63; i >= 32; --i) if (res >> i & 1) {
        res ^= B << (i - 32);
    }
    return res;
}

ull exp(ull x, int b) {
    ull ans = 1;
    for ( ; b > 0; b >>= 1) {
        if (b & 1)
            ans = mul(ans, x);
        x = mul(x, x);
    }
    return ans;
}

ull read(char* s) {
    ull res = 0;
    int temp = -1;
    for (int i = 0; s[i]; ++i) {
        if (isdigit(s[i])) {
            if (temp < 0) temp = 0;
            temp = temp * 10 + s[i] - '0';
        } else {
            if (temp >= 0) res |= 1ull << temp;
            temp = -1;
        }
    }
    if (temp >= 0) res |= 1ull << temp;
    return res;
}

unordered_map<ull, ull> mp;

int main() {
#ifdef Wearry 
    freopen("in", "r", stdin);
#endif

    ull U = exp(2, K), T = U;

    for (int i = 1; i <= (199 * K); ++i) {
        if (1ull * i * K <= UINT_MAX) {
            mp[T] = 1ull * i * K;
            T = mul(T, U);
        }
    }

    mp[1] = (1ull << 32) - 1;

    while (scanf("%s", str) && str[0] != '0') {
        ull y = read(str), z = 2;

        for (int i = 1; i <= K; ++i) {
            if (mp.count(mul(z, y))) {
                printf("%llu\n", mp[mul(z, y)] - i);
                break;
            }
            z = mul(z, 2);
        }
    }
    return 0;
}
