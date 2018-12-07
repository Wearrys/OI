#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back
#define REP(i, a, b)  for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i=(a-1), i##end = (b); i >=i##end; --i)

template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int N = 100000;
const int oo = 0x3f3f3f3f;

template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}
string solve(int a, int b, int c) {
    bool flag = false;

    if(!a) {
        flag = true;
        a = b;
        b = c;
        c = 0;
    }

    string res;
    if(!a) {
        res = string(b, 'b');
    }else {
        if(!b && !c) {
            res = string(a, 'a');
        }else {
            vector<string> ans(a, "a");
            for(int i = 0; i < c; ++i) ans[i % a] += 'c';

            int pos = c % a;
            for(int i = 0; i < b; ++i) {
                ans[pos] += 'b';
                if(++ pos == a) pos = c % a; 
            }

            map<string, int> mp;
            vector< pair<string, int> > sub;

            for(const auto& x : ans) { ++ mp[x]; }
            for(const auto& x : mp) { sub.pb(x); }
            while(sub.size() < 3) sub.pb(make_pair("", 0));

            string tmp = solve(sub[0].snd, sub[1].snd, sub[2].snd);

            for(const auto& x : tmp) {
                res += sub[x - 'a'].fst;
            }
        }
    }

    if(flag) {
        for(auto& ch : res) ++ ch;
    }
    return res;
}

int a, b, c;
int main() {
#ifdef Wearry
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif
    
    cin >> a >> b >> c;
    cout << solve(a, b, c) << endl;

    return 0;
}
