#include <bits/stdc++.h>
using namespace std;

const int N = 100;

class TreesAndBrackets {

    int lnk[N + 5];
    stack<int> stk;
    bool dp[N + 5][N + 5];

    public:
        string check(string t1, string t2) {
            int n = t1.length(), m = t2.length();

            memset(dp, 0, sizeof dp);
            dp[0][0] = true;

            for(int i = 0; i < n; ++i) {
                if(t1[i] == '(') {
                    stk.push(i);
                } else {
                    lnk[lnk[i] = stk.top()] = i;
                    stk.pop();
                }
            }

            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < m; ++j) if(dp[i][j]) {
                    if(t1[i] == t2[j]) dp[i + 1][j + 1] = true;
                    else if(lnk[i] > i) {
                        dp[lnk[i] + 1][j] = true;
                    }
                }
            }

            return dp[n][m] ? "Possible" : "Impossible";
        }
};

// CUT begin
ifstream data("TreesAndBrackets.sample");

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

bool do_test(string t1, string t2, string __expected) {
    time_t startClock = clock();
    TreesAndBrackets *instance = new TreesAndBrackets();
    string __result = instance->check(t1, t2);
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
        string t1;
        from_stream(t1);
        string t2;
        from_stream(t2);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(t1, t2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1540258519;
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
        cout << "TreesAndBrackets (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
