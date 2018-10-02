#include <bits/stdc++.h>

using std::pair;
using std::vector;
using std::string;

typedef long long ll;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb(a) push_back(a)
#define mp(a, b) std::make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)

template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;

string procStatus() {
    std::ifstream t("/proc/self/status");
    return string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}

template <typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = 1000;

const char* dir = "RULD";
const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, -1, 0, 1 };

int n;
vector<int> step;
ll x[N + 5], y[N + 5];

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    read(n);
    for(int i = 1; i <= n; ++i) {
        read(x[i]), read(y[i]);

        if(((x[i] + y[i]) ^ (x[1] + y[1])) & 1) {
            return !puts("-1");
        }
    }

    if((x[1] + y[1]) % 2 == 0) step.pb(1);
    for(int i = 0, j = 1; i <= 30; ++i, j <<= 1) step.pb(j);

    printf("%d\n", (int) step.size());
    for(int i = 0; i < (int) step.size(); ++i) printf("%d ", step[i]);
    puts("");

    for(int i = 1; i <= n; ++i) {
        string str;
        for(int j = (int) step.size() - 1; j >= 0; --j) {
            int _dir = 0;
            ll mn = LLONG_MAX;

            for(int d = 0; d < 4; ++d) {
                if(chkmin(mn, std::abs(x[i] + dx[d] * step[j]) + std::abs(y[i] + dy[d] * step[j]))) { 
                    _dir = d;
                }
            }

            //if(j == 0) assert(mn == 0);

            str += dir[_dir]; 
            x[i] += dx[_dir] * step[j];
            y[i] += dy[_dir] * step[j];
        }
        std::reverse(str.begin(), str.end());
        std::cout << str << std::endl;
    }

    return 0;
}
