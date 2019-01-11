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

const int N = 50;
const int S = 1 << 15;

int fail[N + 5];
long long f[S + 5][N + 5], g[S + 5][N + 5];

class RandomConcat {
    public:
    double expectation(vector<string> pieces, string needle) {
        int m = (int) pieces.size();
        int n = (int) needle.length();

        fail[1] = 0;
        for(int i = 1; i < n; ++i) {
            int j = fail[i];
            while(j && needle[j] != needle[i]) j = fail[j];
            fail[i + 1] = j + (needle[j] == needle[i]);
        }

        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);

        auto go = [&] (int u, string s) {
            int res = 0;
            for(int i = 0; i < (int) s.length(); ++i) {
                while(u && needle[u] != s[i]) u = fail[u];

                if(needle[u] == s[i]) ++ u;
                if(u == n) ++ res, u = fail[u];
            }
            return make_pair(res, u);
        };

        g[0][0] = true;
        for(int i = 0; i < (1 << m); ++i) {
            for(int k = 0; k < n; ++k) if(g[i][k]) {
                for(int j = 0; j < m; ++j) if((i >> j & 1) ^ 1) {
                    pair<int, int> temp = go(k, pieces[j]);
                    g[i | (1 << j)][temp.second] += g[i][k];
                    f[i | (1 << j)][temp.second] += f[i][k] + g[i][k] * temp.first;
                }
            }
        }

        double ans = 0.0;
        for(int i = 0; i < n; ++i) ans += f[(1 << m) - 1][i];
        for(int i = 1; i <=m; ++i) ans /= i;

        return ans;
    }
};

// CUT begin
ifstream data("RandomConcat.sample");

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

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<string> pieces, string needle, double __expected) {
    time_t startClock = clock();
    RandomConcat *instance = new RandomConcat();
    double __result = instance->expectation(pieces, needle);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<string> pieces;
        from_stream(pieces);
        string needle;
        from_stream(needle);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(pieces, needle, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1545828171;
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
        cout << "RandomConcat (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
