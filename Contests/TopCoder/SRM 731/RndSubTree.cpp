#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

const int N = 1000;
const int mo = 1e9 + 7;

int fpm(int x, int y) {
    int res = 1;
    for(; y > 0; y >>= 1) {
        if(y & 1)
            res = 1ll * res * x % mo;
        x = 1ll * x * x % mo;
    }
    return res;
}

int binom[N + 5][N + 5];
int f[N + 5], g[N + 5], h[N + 5];

void init() {
    for(int i = 0; i <= N; ++i) {
        binom[i][0] = binom[i][i] = 1;
        for(int j = 1; j < i; ++j) {
            binom[i][j] = (binom[i-1][j] + binom[i-1][j-1]) % mo;
        }
    }
}

typedef long long ll;

class RndSubTree {
    public:
    int count(int n) {

        init();
        memset(h, 0, sizeof h);
        memset(g, 0, sizeof g);
        g[1] = 1, h[1] = 0;

        for(int i = 2; i <= n; ++i) {
            for(int j = 0; j < i; ++j) {
                ll temp = 1ll * binom[i-1][j] * fpm(fpm(2, i - 1), mo - 2);
                h[i] = (h[i] + temp * ((ll)g[j]*(i-j)%mo + (ll)g[i-1-j]*(j+1)%mo+h[j]+h[i-1-j]) % mo) % mo;
                g[i] = (g[i] + temp * (g[j] + g[i-1-j])) % mo;
            }
            g[i] = (g[i] + i) % mo;
        }

        return h[n];
    }
};

// CUT begin
ifstream data("RndSubTree.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int k, int __expected) {
    time_t startClock = clock();
    RndSubTree *instance = new RndSubTree();
    int __result = instance->count(k);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        int k;
        from_stream(k);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1522323568;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "RndSubTree (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
