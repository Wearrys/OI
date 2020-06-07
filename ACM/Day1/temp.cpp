struct hash_map {
    const int N = 2e7;
    const int MOD = 1e6 + 7;

    int head[MOD], cnt;
    int nxt[N], v[N], f[N];

    int& operator [] (int w) {
        int u = w % MOD;

        for (int i = head[u]; i; i = nxt[i]) {
            if (v[i] == w) {
                return f[i];
            }
        }

        ++ cnt;
        nxt[cnt] = head[u];
        v[cnt] = w;
        head[u] = cnt;

        return f[cnt];
    }
};
