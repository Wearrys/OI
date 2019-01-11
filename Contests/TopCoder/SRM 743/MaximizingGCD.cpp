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

class MaximizingGCD {
    public:
    int maximumGCDPairing(vector<int> A) {

        auto chk = [&] (int d) {
            vector<int> B;
            static bool vis[50 + 5];

            for(int i = 0; i < (int) A.size(); ++i) {
                vis[i] = false;
                B.push_back(A[i] % d);
            }
            for(int i = 0; i < (int) B.size(); ++i) if(!vis[i]) {
                for(int j = i + 1; j < (int) B.size(); ++j) if(!vis[j] && (B[i] + B[j]) % d == 0) {
                    vis[i] = vis[j] = true;
                    break;
                }
                if(!vis[i]) return false;
            }
            return true;
        };

        int ans = 1;
        long long sum = 0;
        for(auto a : A) sum += a;

        if(chk(sum)) ans = sum;

        for(int i = 2; 1ll * i * i <= sum; ++i) if(sum % i == 0) {
            if(chk(i)) ans = max(ans, i);
            if(chk(sum / i)) ans = max(ans, (int) (sum / i));
        }
        return ans;
    }
};

// CUT begin
ifstream data("MaximizingGCD.sample");

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

bool do_test(vector<int> A, int __expected) {
    time_t startClock = clock();
    MaximizingGCD *instance = new MaximizingGCD();
    int __result = instance->maximumGCDPairing(A);
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
        vector<int> A;
        from_stream(A);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1546952147;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "MaximizingGCD (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
