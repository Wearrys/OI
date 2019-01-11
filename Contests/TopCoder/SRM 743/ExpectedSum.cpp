#include <bits/stdc++.h>

using namespace std;

typedef map<pair<int, int>, double> atom;

#define mp(a, b) make_pair(a, b)

const int N = 50;

class ExpectedSum {
    public:
        atom f[N + 5];
        double solve(vector<int> sequence, vector<int> probMinus) {
            int n = (int) sequence.size();

            f[0][mp(0, 0)] = 1.0;

            for(int i = 0; i < n; ++i) {
                int c;
                for(auto x : f[i]) {
                    c = max(0, x.first.first + sequence[i]);
                    f[i + 1][mp(c, max(c, x.first.second))] += x.second * (100 - probMinus[i]) / 100.0;
                    c = max(0, x.first.first - sequence[i]);
                    f[i + 1][mp(c, max(c, x.first.second))] += x.second * probMinus[i] / 100.0;
                }
            }

            double ans = 0.0;
            for(auto x : f[n]) {
                ans += x.first.second * x.second;
            }

            return ans;
        }
};

// CUT begin
ifstream data("ExpectedSum.sample");

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

bool do_test(vector<int> sequence, vector<int> probMinus, double __expected) {
    time_t startClock = clock();
    ExpectedSum *instance = new ExpectedSum();
    double __result = instance->solve(sequence, probMinus);
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
        vector<int> sequence;
        from_stream(sequence);
        vector<int> probMinus;
        from_stream(probMinus);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(sequence, probMinus, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1547170902;
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
        cout << "ExpectedSum (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
