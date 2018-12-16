#include <bits/stdc++.h>
using namespace std;

const int N = 300000;
const int mo = 998244353;

int read(int& x) {
    x = 0;
    char ch = getchar(); 
    while(!isdigit(ch)) ch = getchar();
    while(isdigit(ch)) x = (x * 10ll + ch - '0') % mo, ch = getchar();
    return x;
}

struct seq {
    int hsh;
    int a[3];

    void merge(const seq& rhs, const int& c) {
        hsh = (hsh + 1ll * rhs.hsh * c) % mo;
        for(int i = 0; i < 3; ++i) {
            a[i] = (a[i] + rhs.a[i]) % mo;
        }
    }
};

int pw[N + 5];
seq f[N + 5][3];

void init() {
    pw[0] = 233; 
    for(int i = 1; i <= N; ++i) pw[i] = 1ll * pw[i-1] * pw[i-1] % mo;

    f[0][0].hsh = 'P', f[0][0].a[0] = 1;
    f[0][1].hsh = 'R', f[0][1].a[1] = 1;
    f[0][2].hsh = 'S', f[0][2].a[2] = 1;

    for(int i = 1; i <= N; ++i) {
        f[i][0] = f[i-1][0], f[i][0].merge(f[i-1][1], pw[i-1]);
        f[i][1] = f[i-1][0], f[i][1].merge(f[i-1][2], pw[i-1]);
        f[i][2] = f[i-1][1], f[i][2].merge(f[i-1][2], pw[i-1]);
    }
}

int n, op;
int r, p, s;

int main() {
    freopen("in", "r", stdin);
    init();

    scanf("%d%d", &n, &op);
    read(r), read(s), read(p);

    int flag = -1;
    for(int i = 0; i < 3; ++i) {
        if(p != f[n][i].a[0] || r != f[n][i].a[1] || s != f[n][i].a[2]) {

        } else {
            flag = i;
            break;
        }
    }

    auto lc = [&] (int x) { return (x <= 1) ? 0 : 1; };
    auto rc = [&] (int x) { return (x >= 1) ? 2 : 1; };  

    function<void(int, int, char*, char*, int)> dfs = [&] (int dep, int type, char* L, char* R, int t) {
        if(dep == 0) {
            printf("%c", (type == 0) ? 'P' : (type == 1 ? 'R' : 'S'));
            return;
        }

        if(!t) {
            if(L[n - dep] == R[n - dep]) {
                if(L[n - dep] == '0') dfs(dep - 1, lc(type), L, R, t);
                else dfs(dep - 1, rc(type), L, R, t);
            } else {
                dfs(dep - 1, lc(type), L, R, 1);
                dfs(dep - 1, rc(type), L, R, 2);
            }
        } else if(t == 1) {
            if(L[n - dep] == '0') {
                dfs(dep - 1, lc(type), L, R, t);
                dfs(dep - 1, rc(type), L, R, 3);
            } else dfs(dep - 1, rc(type), L, R, t);
        } else if(t == 2) {
            if(R[n - dep] == '1') {
                dfs(dep - 1, lc(type), L, R, 3);
                dfs(dep - 1, rc(type), L, R, t);
            } else dfs(dep - 1, lc(type), L, R, t);
        } else {
            dfs(dep - 1, lc(type), L, R, t);
            dfs(dep - 1, rc(type), L, R, t);
        }
    };

    if(flag == -1) 
        puts("-1");
    else {
        if(op & 1) printf("%d\n", f[n][flag].hsh);
        if(op & 2) { 
            static char L[N + 5], R[N + 5];
            scanf("%s%s", L, R);
            dfs(n, flag, L, R, 0);
        }
    }

    return 0;
}
