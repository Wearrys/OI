#include <bits/stdc++.h>
using namespace std;

const int N = 200000;
const int oo = 0x3f3f3f3f;

int n;
int a[N + 5], size[N + 5];
stack<pair<int*, int> > stk;

struct BIT {
#define lowbit(x) (x & -x)
    int c[N + 5]; 

    void clear() { memset(c, ~oo, sizeof c); }
    void modify(int x, int y) {
        while(x <= n) {
            if(c[x] < y) {
                stk.emplace(c + x, c[x]); 
            }
            c[x] = max(c[x], y);
            x += lowbit(x);
        }
    }

    int query(int x) {
        int res = c[N + 1];
        while(x > 0) {
            res = max(res, c[x]);
            x -= lowbit(x);
        }
        return res;
    }
};

BIT bit[2];
bool vis[N + 5];
vector<int> key;

bool chk(int A, int B, int x, int y, int c) {
    int t;
    t = B - A + c;
    if((t >= 0) && bit[t & 1].query(n - x) >= t) return true;
    t = A - B + c;
    if((t >= 0) && bit[t & 1].query(n - y) >= t) return true;
    return false;
}

int main() {

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", a + i);

        if(key.empty() || a[i] > key.back()) {
            vis[i] = true;
            key.push_back(a[i]);
        }
    }

    bit[1].clear();
    for(int i = n; i >= 1; --i) {
        size[i] = stk.size();
        if(vis[i]) {
            bit[0].modify(n - a[i] + 1, bit[0].query(n - a[i]) + 2);
            bit[1].modify(n - a[i] + 1, bit[1].query(n - a[i]) + 2);
        } else {
            bit[0].modify(n - a[i] + 1, bit[1].query(n - a[i]) + 1);
            bit[1].modify(n - a[i] + 1, bit[0].query(n - a[i]) + 1);
        }
    }

    int c = key.size();
    if(bit[c & 1].query(n) < c) return puts("-1"), 0;

    int A = 0, B = 0, x = 0, y = 0;

    for(int i = 1; i <= n; ++i) {
        c -= vis[i];
        while((int) stk.size() > size[i]) {
            *stk.top().first = stk.top().second;
            stk.pop();
        }

        int nx = x, nA = A;
        if(a[i] > x) ++ A, x = a[i];
        
        if(chk(A, B, x, y, c)) {
            putchar('0');
            continue;
        }

        putchar('1');
        x = nx, A = nA;
        if(a[i] > y) ++ B, y = a[i];
    }

    return 0;
}
