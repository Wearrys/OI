#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 21;
const int oo = 0x3f3f3f3f;

template <typename T> inline bool chkmin(T& a, T b) {
    return a > b ? a = b, 1 : 0;
}

int dis[N + 5];
int pre[N + 5];

void solve(int len) {
    queue<int> q;
    memset(dis, oo, sizeof dis);

    q.push(0);
    dis[0] = 0;
    while(!q.empty()) {
        int x = q.front(); q.pop();

        for(int i = 0; i < len; ++i) {
            for(int j = 1; j <= i && i + j < len; ++j) {
                int st = (1 << i) | (1 << (i-j)) | (1 << (i+j));

                if(chkmin(dis[x ^ st], dis[x] + 1)) {
                    pre[x ^ st] = st;
                    q.push(x ^ st);
                }
            }
        }
    }
}

int n;
int a[N + 5];

set<int> s;
vector<vector<int> > ans;

inline void rev(int x) {
    if(a[x] ^= 1) {
        s.insert(x);
    } else {
        s.erase(x);
    }
}

inline void print(int x, int y, int z) {
    rev(x), rev(y), rev(z);
    ans.push_back((vector<int>) { x, y, z });
}

inline void print(int st) {
    vector<int> t;
    for(int i = 0; i < 12; ++i) if(st >> i & 1) {
        rev(i);
        t.push_back(i);
    }
    ans.push_back(t);
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
#endif

    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        if(a[i]) { s.insert(i); }
    }

    while(!s.empty() && (*s.rbegin()) >= 12) {
        int x = *s.rbegin(); 

        if(a[x - 2] && a[x - 1]) {
            print(x - 2, x - 1, x);
        } else if(!a[x - 2] && !a[x - 1]) {
            print(x - 6, x - 3, x);
        } else if(a[x - 2] && !a[x - 1]) {
            print(x - 4, x - 2, x);
        } else {
            int cnt = 0;
            for(int i = x - 5; i < x - 2; ++i) {
                cnt += a[i];
            }

            if(cnt == 0) {
                print(x - 7, x - 4, x - 1);
                print(x - 8, x - 4, x);
            } else if(cnt == 1) {
                for(int i = x - 5; i < x - 2; ++i) if(a[i]) {
                    print(i - (x - i), i, x);
                    print(x - 11, x - 6, x - 1);
                }
            } else if(cnt == 2) {
                int c = 0;
                for(int i = x - 5; i < x - 2; ++i) if(a[i]) {
                    if(c) {
                        print(i - (x - i), i, x);
                    } else {
                        print(i - (x - 1 - i), i, x - 1); 
                        c = 1;
                    }
                }
            } else {
                print(x - 5, x - 3, x - 1);
                print(x - 8, x - 4, x);
            }
        }
    }

    solve(n = std::min(n, 12));
    int cur = 0;
    for(int i = 0; i < n; ++i) cur |= (a[i] << i);

    if(dis[cur] == oo) {
        puts("NO");
        return 0;
    }

    while(cur) print(pre[cur]), cur ^= pre[cur];

    puts("YES");
    printf("%d\n", (int) ans.size());
    for(auto x : ans) {
        for(auto y : x) printf("%d ", y + 1);
        puts("");
    }

    return 0;
}
