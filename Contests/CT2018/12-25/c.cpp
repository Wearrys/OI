#include <bits/stdc++.h>
using namespace std;

const int N = 1000;
const int mo = 1e9 + 7;

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = 1ll * res * x % mo;
        x = 1ll * x * x % mo;
    }
    return res;
}

int p, q, s, m, k;
bitset <1 << 10> C[N + 5], R[N + 5], B[N + 5], T;
int f[N + 5][N + 5], g[N + 5][N + 5], pw[N*N + 5];

void init() {
    pw[0] = 1;
    for(int i = 1; i <= N*N; ++i) pw[i] = pw[i-1] * 2 % mo;

    g[0][0] = f[0][0] = 1;
    for(int i = 0; i <= N; ++i) {
        for(int j = 0; j <= N; ++j) {
            f[i + 1][j] = (f[i + 1][j] + 1ll * f[i][j] * pw[j]) % mo;
            f[i + 1][j + 1] = (f[i + 1][j + 1] + 1ll * f[i][j] * (pw[p] - pw[j] + mo)) % mo;

            g[i + 1][j] = (g[i + 1][j] + 1ll * g[i][j] * pw[j]) % mo;
            g[i + 1][j + 1] = (g[i + 1][j + 1] + 1ll * g[i][j] * (pw[s] - pw[j] + mo)) % mo;
        }
    }
}

int r = 0;

void modify(int x) {

    int pos = -1;
    vector<int> vec;
    for(int i = 1; i <= p; ++i) if(R[i][x]) {
        vec.push_back(i);
        pos = i;
    }

    for(int i = 0; i < (int) vec.size() - 1; ++i) {
        C[vec[i]] ^= C[pos];
        R[vec[i]] ^= R[pos];
    }
    C[pos] ^= B[x] ^ T;

    for(int i = 1; i <= p; ++i) if(C[i].any() && i != pos) {
        int c = C[i]._Find_first();

        if(C[pos][c]) {
            C[pos] ^= C[i];
            R[pos] ^= R[i];
        }
    }

    x = C[pos]._Find_first();
    while(pos > 1 && x < (int) C[pos-1]._Find_first()) swap(C[pos], C[pos-1]), swap(R[pos], R[pos-1]), -- pos;
    while(pos < p && x > (int) C[pos+1]._Find_first()) swap(C[pos], C[pos+1]), swap(R[pos], R[pos+1]), ++ pos;

    r = 0;
    for(int i = 1; i <= p; ++i) {
        r += (C[i].any());
    }
}

int calc() {
    int ans = 0;
    for(int i = r; i <= q; ++i) {
        ans = (ans + 1ll * f[q][i] * g[i][r] % mo * pw[(q - i) * s]) % mo;
    }
    ans = 1ll * ans * fpm(g[p][r], mo - 2) % mo;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> p >> q >> s >> m >> k;

    init();
    for(int i = 1; i <= p; ++i) {
        for(int j = 1; j <= s; ++j) {
            static int x;
            if(cin >> x, x) C[i].set(j);
        }
        B[i] = C[i];
        R[i].set(i);
    }

    for(int i = 1; i <= s; ++i) {
        for(int j = r+1; j <= p; ++j) {
            if(C[j][i]) {
                std::swap(C[r+1], C[j]);
                std::swap(R[r+1], R[j]);
                break;
            }
        }
        if(!C[r+1][i]) continue;
        for(int j = r+2; j <= p; ++j) if(C[j][i]) C[j] ^= C[r+1], R[j] ^= R[r+1];
        ++ r;
    }

    int lans;
    cout << (lans = calc()) << endl;

    for(int i = 1; i <= m; ++i) {
        static int x, y;
        cin >> x;
        if(k) x ^= lans;

        T.reset();
        for(int j = 1; j <= s; ++j) if(cin >> y, y) T.set(j);

        modify(x);
        B[x] = T;
        cout << (lans = calc()) << endl;
    }

    return 0;
}
