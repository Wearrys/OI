#include<bits/stdc++.h>
using namespace std;

int n;
int _in() { printf("I\n"); return ++n; }
int _S(int x) { printf("S %d\n", x); return ++n; }
int _out(int x) { printf("O %d\n", x); return ++n; }
int _neg(int x) { printf("- %d\n", x); return ++n; }
int _add(int x, int y) { printf("+ %d %d\n", x, y); return ++n; }
int _left(int x, int y) { printf("< %d %d\n", x, y); return ++n; }
int _rigt(int x, int y) { printf("> %d %d\n", x, y); return ++n; }
int _addc(int x, string s) { printf("C %d %s\n", x, s.c_str()); return ++n; }

struct node {
    int id;
    void in() { id = _in(); }
    void out() { _out(id); }
    node(int _id = 0):id(_id) {}
};

node operator - (node a) { return node(_neg(a.id)); }
node operator << (node a, int b) { return node(_left(a.id, b)); }
node operator >> (node a, int b) { return node(_rigt(a.id, b)); }
node operator + (node a, string b) { return node(_addc(a.id, b)); }

node operator + (node a, node b) {
    if(!a.id || !b.id) 
        return node(a.id | b.id);
    return node(_add(a.id, b.id));
}
node S(node a) { return node(_S(a.id)); }

string pw[200], _pw[200];
void bit_div(node a, node* bit) {
    a = a << 100;
    for(int i = 31; i >= 0; i--) {
        if(i == 0) { bit[31] = -a; break; }

        node cur = -S(a + ("-" + _pw[i+100]));
        bit[31-i] = cur << (i + 100);
        a = a + bit[31-i];
    }
}
node operator * (node a, node b) {
    node bitb[50] = {0};
    bit_div(b, bitb);

    node ans, A = a >> 200;
    for(int i = 0; i < 32; ++i) {
        node cur = bitb[i] + pw[131 - i];
        ans = ans + ((S(A + cur) + -S(cur)) << (202 + 31 - i));
    }
    return ans;
}
node operator / (node a, node b) {
    a = a << 100;
    node ans, B = b >> 200, _b = -b;
    for(int i = 63; i >= 0; --i) {
        if(i == 0) {
            ans = ans + S(a + (_b << (100 + i)) + pw[90]); 
            break;
        }
        node cur = S(a + (_b << (100 + i)) + pw[90]);
        node sig = (-cur + "1") << 500;
        ans = ans + (cur << i);
        a = a + -((S(sig + B) + -S(sig)) << (302 + i));
    }
    return ans;
}
node operator % (node a, node b) {
    return a + -((a/b) * b);
}

node x, y, m;
node solve() { return x * y % m; }

int main() {
    static char str[100000];
    for(int i = 0; i < 200; ++i) {
        sprintf(str, "%.0lf", pow(2.0, i));
        pw[i] = string(str);

        sprintf(str, "%.0lf", pow(2.0, i) - pow(2.0, 60));
        _pw[i] = string(str);
    }

    freopen("nodes10.out", "w", stdout);

    x.in(), y.in(), m.in();
    solve().out();

    return 0;
}
