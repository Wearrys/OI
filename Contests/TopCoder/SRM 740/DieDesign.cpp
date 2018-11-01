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

template <typename T> inline bool chkmax(T& a, T b) {
    return a < b ? a = b, 1 : 0;
}

class DieDesign {
    static const int N = 30;
    static const int M = N * 5000;
    static const int oo = 0x3f3f3f3f;

    public:

    int n, s = 0;
    int dp[N + 5][M + 5];
    int pre[N + 5][M + 5];

    vector<int> design(vector<int> pips) {
        vector<int> ans;
        n = (int) pips.size();
        for(auto v : pips) s += v;

        sort(pips.begin(), pips.end());
        pips.erase(unique(pips.begin(), pips.end()), pips.end());

        for(auto& v : pips) v ++;
        pips.push_back(0);
        sort(pips.begin(), pips.end());

        memset(dp, ~oo, sizeof dp);
        dp[0][0] = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j <= s; ++j) if(dp[i][j] >= 0) {
                for(int k = 0; k < (int) pips.size() && j + pips[k] <= s; ++k) {
                    if(chkmax(dp[i + 1][j + pips[k]], dp[i][j] + k)) {
                        pre[i + 1][j + pips[k]] = pips[k];
                    }
                }
            }
        }

        int mx = 0;
        for(int i = 0; i <= s; ++i) {
            chkmax(mx, dp[n][i]);
        }
        for(int i = 0; i <= s; ++i) if(dp[n][i] == mx) {
            int t = s - i;
            while(n > 0) {
                ans.push_back(pre[n][i]); 
                i -= pre[n][i];
                -- n;
            }
            ans[0] += t;
            break;
        }

        return ans;
    }
};

// CUT begin
ifstream data("DieDesign.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<int> pips, vector<int> __expected) {
    time_t startClock = clock();
    DieDesign *instance = new DieDesign();
    vector<int> __result = instance->design(pips);
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
        vector<int> pips;
        from_stream(pips);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(pips, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1541042310;
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
        cout << "DieDesign (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
