#include <bits/stdc++.h>
#include <tr1/unordered_map>
 
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
 
template<typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48; 
    return x *= f;
}

const int N = 100;
const int mo = 998244353;

inline string get_substr(const string& x, int l, int sl) {
    string tmp, res;

    for(int i = 0; i < sl; ++i) res += '1';
    for(int i = 0; i < l; i += sl) {
        tmp = x.substr(i, sl);
        
        for(int j = 0; j < sl; ++j) {
            res[j] = ((res[j] - '0') && (tmp[j] - '0')) + '0';
        }
    }
    return res;
}

std::tr1::unordered_map<string, int> mp;

int dp(string x) {

    if(mp.count(x)) return mp[x];

    int len = x.length();
    int res = 1ll * dp(x.substr(0, len-1)) * dp(x.substr(len-1, 1)) % mo;

    for(int i = 1; i <= len; ++i) {
        for(int j = i+i; j <= len; j += i) {

            string lft = x.substr(0, len - j);
            string rht = get_substr(x.substr(len - j, j), j, i);

            res = (res + 1ll * dp(lft) * dp(rht)) % mo;
        }
    }
    return mp[x] = res;
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif 

    string st;
    std::cin >> st;

    mp[""] = 1;
    mp["0"] = 1; 
    mp["1"] = 2;

    printf("%d\n", dp(st));

    return 0;
}
