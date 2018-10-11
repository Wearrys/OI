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

class DigitRotation {

#define fst first
#define snd second
    
    typedef long long ll;
    const int N = 500;
    const int mo = 998244353;

    public:
    int sumRotations(string X) {
        pair<int, int> sum[N + 5];
        int n = (int) X.length(), tot = 0;

        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                for(int k = j + 1; k < n; ++k) if(i || X[k] != '0') {
                    ++ tot;
                    sum[k].fst ++, sum[k].snd += X[j] - '0';
                    sum[j].fst ++, sum[j].snd += X[i] - '0';
                    sum[i].fst ++, sum[i].snd += X[k] - '0';
                }
            }
        }
        int x = 1, ans = 0;
        for(int i = n-1; i >= 0; --i) {
            ans = (ans + (ll) x * ((ll) (tot - sum[i].fst) * (X[i]-'0') % mo + sum[i].snd) % mo) % mo;
            x = x * 10ll % mo;
        }
        return ans;
    }
};

// CUT begin
ifstream data("DigitRotation.sample");

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

bool do_test(string X, int __expected) {
    time_t startClock = clock();
    DigitRotation *instance = new DigitRotation();
    int __result = instance->sumRotations(X);
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
        string X;
        from_stream(X);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(X, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1534473398;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "DigitRotation (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
