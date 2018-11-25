#include <bits/stdc++.h>

using std::string;

string to_str(int x, int len = 0) {
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

    string res = "0";
    for(int i = top - 1; i >= 0; --i) {
        res += "9*";
        res += char(stk[i] + '0');
        res += "+";
    }

    if(flag) res = '0' + res + '-';
    while((int) res.length() < len) res = res + '0' + '+';

    return res;
}

string read(string x)  { return x + '<'; }
string read(int x) { return read(to_str(x)); }
string write(string x) { return x + '>'; }
string write(int x) { return write(to_str(x)); }

// val(x) > 0
string condition(string x) { return x + '0' + ':' + '1' + '-'; }

string branch(string a, string b) { return a + to_str((int) b.length()) + '?' + b; }
string repeat(string a, string b) {
    int len = (int) (a.length() + b.length());
    return a + b + to_str(- len - 28, 27) + '?';
}

string add(string x, string y) { return x + y + '+'; }
string sub(string x, string y) { return x + y + '-'; }
string mul(string x, string y) { return x + y + '*'; }
string div(string x, string y) { return x + y + '/'; }

string Main, rep0, rep1, swap;

int main() {
    freopen("6", "w", stdout);

    Main += 'r' + write(100);
    rep0 = 'r' + write(read(101)) + add(read(101), "1") + write(101);
    rep0 = '0' + write(101) + repeat(rep0, condition(sub(read(100), read(101))));
    Main += rep0;

    swap = read(read(102)) + write(103) + read(read(101)) + write(read(102)) + read(103) + write(read(101));
    rep0 = branch(condition(sub(read(read(101)), read(read(102)))), swap) + add(read(102), "1") + write(102);
    rep1 = read(101) + write(102) + repeat(rep0, condition(sub(read(100), read(102)))) + add(read(101), "1") + write(101);
    Main += '0' + write(101) + repeat(rep1, condition(sub(read(100), read(101))));

    Main += read(div(read(100), "2")) + 'p';

    std::cout << Main << std::endl;
    return 0;
}
