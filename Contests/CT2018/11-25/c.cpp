#include <bits/stdc++.h>

using std::string;

typedef long long ll;

string to_str(ll x, int len = 0) {
    static int stk[1005];
    int top = 0, flag = 0;

    if(x < 0) {
        x = -x;
        flag = 1;
    }

    while(x > 0) {
        stk[top ++] = x % 9;
        x /= 9;
    }

    string res = char(stk[top-1] + '0');
    for(int i = top - 2; i >= 0; --i) {
        res += "9*";
        res += char(stk[i] + '0');
        res += "+";
    }

    if(flag) res = "0" + res + "-"; 
    while((int) res.length() < len) res = res + '0' + '+';

    return res;
}

string r(string x) { return x + '<'; }
string w(string x) { return x + '>'; }

string r(ll x) { return r(to_str(x)); }
string w(ll x) { return w(to_str(x)); }

string add(string x, string y) { return x + y + '+'; }
string sub(string x, string y) { return x + y + '-'; }
string mul(string x, string y) { return x + y + '*'; }
string div(string x, string y) { return x + y + '/'; }

// val(x) > 0 ? 0 : 1
string condit(string x) { return x + '0' + ':' + '1' + '-'; }
string branch(string a, string b) { return a + to_str((int) b.length()) + '?' + b; }
string repeat(string a, string b) {
    int len = (int) (a.length() + b.length());
    return a + b + to_str(- len - 12, 11) + '?';
}

long long oo = (ll) 1e15;
int n = 0, m = 1, i = 2, j = 3, k = 4;

string Main, rep, rep1, swap;
string g(int x, int y) { return add(add(mul(r(x), r(n)), r(y)), "5"); }

int main() {
    freopen("data8.out", "w", stdout);

    Main += 'r' + w(n) + 'r' + w(m);

    rep = to_str(oo) + w(g(i, j)) + add(r(j), "1") + w(j);
    rep = '0'+w(j) + repeat(rep, r(j) + r(n) + ':' + '1' + '+') + add(r(i), "1") + w(i);
    rep = '0'+w(i) + repeat(rep, r(i) + r(n) + ':' + '1' + '+');

    Main += rep;

    rep = '0' + w(g(i, j)) + add(r(i), "1") + w(i);
    rep = '0'+w(i) + repeat(rep, r(i) + r(n) + ':' + '1' + '+');

    Main += rep;

    rep = 
        "r1-"+w(j) + 
        "r1-"+w(k) + 
        'r' + w(g(j, k)) + 
        r(g(j, k)) + w(g(k, j)) + 
        add(r(i), "1") + w(i);

    Main += '0'+w(i) + repeat(rep, r(i) + r(m) + ':' + '1' + '+');

    string ji = g(j,i);//add(mul(r(j), r(n)), r(i));
    string ik = g(i,k);//add(mul(r(i), r(n)), r(k));
    string jk = g(j,k);//add(mul(r(j), r(n)), r(k));

    rep = branch(r(jk) + add(r(ji), r(ik)) + ':'+'1'+'+', add(r(ji), r(ik)) + w(jk)) + add(r(k), "1") + w(k);
    rep = '0'+w(k) + repeat(rep, r(k) + r(n) + ':' + '1' + '+') + add(r(j), "1") + w(j);
    rep = '0'+w(j) + repeat(rep, r(j) + r(n) + ':' + '1' + '+') + add(r(i), "1") + w(i);
    rep = '0'+w(i) + repeat(rep, r(i) + r(n) + ':' + '1' + '+');

    Main += rep;
    Main += '0' + w(j);

    rep = add(r(j), r(add(r(i), "5"))) + w(j) + add(r(i), "1") + w(i);
    rep = '1'+w(i) + repeat(rep, r(i) + r(n) + ':' + '1' + '+');

    Main += rep + r(j) + 'p';

    std::cout << Main << std::endl;

    return 0;
}
