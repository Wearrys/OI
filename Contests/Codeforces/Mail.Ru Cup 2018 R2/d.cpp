#include <bits/stdc++.h>
using namespace std;

const int N = 3000;

string S, T;
string s[N + 5], t[N + 5];

int n;
int l[N + 5], r[N + 5];

int find(const string& a, const string& b) {

    static int fail[N + 5];
    int _n = (int) a.length(), _m = (int) b.length();
    
    fail[0] = fail[1] = 0;
    for(int i = 1; i < _m; ++i) {
        int j = fail[i];
        while(j && b[j] != b[i]) j = fail[j];
        if(b[j] == b[i]) ++ j;
        fail[i+1] = j;
    }

    int j = 0;
    for(int i = 0; i < _n; ++i) {
        while(j && a[i] != b[j]) j = fail[j];
        if(a[i] == b[j]) ++ j;
        if(j == _m) return i - _m + 1;
    }
    return -1;
}

void chk() {
    for(int i = 1; i <= n; ++i) {
        if(r[i] == -1) {
            if(find(s[i], S) != -1) { puts("NO"); exit(0); }
        } else {
            if(find(s[i], S) != l[i]) { puts("NO"); exit(0); }
        }
    }
}

int main() {
#ifdef Wearry
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    ios::sync_with_stdio(false);

    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> s[i];
    for(int i = 1; i <= n; ++i) {
        l[i] = r[i] = -1;

        cin >> t[i];
        if(s[i] != t[i]) {
            for(int j = 0; j < (int) s[i].length(); ++j) if(s[i][j] != t[i][j]) { l[i] = j; break; }
            for(int j = (int) s[i].length() - 1; j >= 0; --j) if(s[i][j] != t[i][j]) { r[i] = j; break; }

            string x = s[i].substr(l[i], r[i] - l[i] + 1);
            string y = t[i].substr(l[i], r[i] - l[i] + 1);

            if(S == "") {
                S = x, T = y;
            } else {
                if(S != x || T != y) return puts("NO"), 0;
            }
        }
    }

    for(bool flag = true; flag;) {
        char c = '&';
        for(int i = 1; i <= n; ++i) if(r[i] != -1) {
            if(l[i] > 0 && (c == '&' || c == s[i][l[i]-1])) {
                c = s[i][l[i]-1];
            } else {
                flag = false;
                break;
            }
        }
        if(flag) {
            S = c + S;
            T = c + T;
            for(int i = 1; i <= n; ++i) if(r[i] != -1) -- l[i];
        }
    }

    for(bool flag = true; flag;) {
        char c = '&';
        for(int i = 1; i <= n; ++i) if(r[i] != -1) {
            if(r[i]+1 < (int) s[i].length() && (c == '&' || c == s[i][r[i]+1])) {
                c = s[i][r[i]+1];
            } else {
                flag = false;
                break;
            }
        }
        if(flag) {
            S = S + c;
            T = T + c;
            for(int i = 1; i <= n; ++i) if(r[i] != -1) ++ r[i]; 
        }
    }

    chk();

    cout << "YES" << endl;
    cout << S << '\n' << T << endl;

    return 0;
}
