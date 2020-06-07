#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 105;
const int mo = 998244353;

struct mat {
    int a[N][N];

    mat(bool type = 0) {
        memset(a, 0, sizeof a);

        if (type) {
            for (int i = 0; i < N; ++i) a[i][i] = 1;
        }
    }

    mat operator * (const mat& b) const {
        mat c;
        for (int i = 0; i < N; ++i) 
            for (int j = 0; j < N; ++j)
                for (int k = 0; k < N; ++k) 
                    c.a[i][k] = (c.a[i][k] + 1ll * a[i][j] * b.a[j][k]) % mo;
        return c; 
    }

    mat operator ^ (int b) const {
        mat ans(1), c = *this;

        for (; b > 0; b >>= 1) {
            if (b & 1)
                ans = ans * c;
            c = c * c;
        }
        return ans;
    }
};

int n, L;
int ch[N][26], fail[N];

bool tag[N];

int rt = 0, cnt = 0;
void insert(char* s) {
    int u = rt;
    for (int i = 0; s[i]; ++i) {
        int c = s[i] - 'a';

        if (!ch[u][c]) 
            ch[u][c] = ++ cnt;
        u = ch[u][c];
    }
    tag[u] = true;
}

void build_fail() {
    queue<int> que;
    for (int c = 0; c < 26; ++c) if (ch[rt][c]) {
        fail[ch[rt][c]] = rt;
        que.push(ch[rt][c]);
    }

    while (!que.empty()) {
        int x = que.front(); que.pop();

        for (int c = 0; c < 26; ++c) {
            int y = ch[x][c];

            if (y) {
                que.push(y);
                fail[y] = ch[fail[x]][c]; 
            } else {
                ch[x][c] = ch[fail[x]][c];
            }
        }

        tag[x] |= tag[fail[x]];
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
#endif

    scanf("%d%d", &n, &L);
    
    for (int i = 0; i < n; ++i) {
        static char str[N];
        scanf("%s", str);
        insert(str);
    }

    build_fail();

    mat t;

    for (int i = rt; i <= cnt; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (!tag[ch[i][j]]) {
                ++ t.a[i][ch[i][j]];
            }
        }
    }

    t = t ^ L;

    int ans = 0;
    for (int i = 0; i < N; ++i) ans = (ans + t.a[0][i]) % mo;
    printf("%d\n", ans);

    return 0;
}
