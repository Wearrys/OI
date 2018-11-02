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

class DigitStringDiv1 {
    public:
    long long count(string S, int X) {

        long long ans = 0;
        vector<long long> vec;

        int n = S.length(), m = n >> 1;

        for(int i = 1; i < (1 << m); ++i) {
            bool flag = true;
            long long c = 0;

            for(int j = 0; j < m; ++j) if(i >> j & 1) {
                if(c == 0) {
                    if(S[j] == '0') {
                        flag = false;
                        break;
                    } else if(__builtin_popcount(i) >= 10) {
                        c = WINT_MAX;
                        break;
                    }
                }

                c = c * 10 + S[j] - '0';
            }

            if(c > X) ++ ans;
            if(flag) {
                vec.push_back(c);
            }
        }

        std::sort(vec.begin(), vec.end());

        for(int i = 1; i < (1 << (n - m)); ++i) {
            int flag = 1;
            long long c = 0, k = 1;

            for(int j = 0; j < n - m; ++j) if(i >> j & 1) {
                if(c == 0) {
                    if(S[j + m] == '0') flag = 0;
                    if(flag == 1 && __builtin_popcount(i) >= 10) {
                        flag = -1;
                        ans += vec.size() + 1;
                        break;
                    }
                }
                k = k * 10;
                c = c * 10 + S[j + m] - '0';
            }

            if(flag != -1) {
                ans = ans + vec.size();
                if(c > X && flag) ans ++;

                if(c > X % k) {
                    ans -= std::lower_bound(vec.begin(), vec.end(), X / k) - vec.begin();
                } else {
                    ans -= std::upper_bound(vec.begin(), vec.end(), X / k) - vec.begin();
                }
            }
        }

        return ans;
    }
};

// CUT begin
ifstream data("DigitStringDiv1.sample");

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

bool do_test(string S, int X, long long __expected) {
    time_t startClock = clock();
    DigitStringDiv1 *instance = new DigitStringDiv1();
    long long __result = instance->count(S, X);
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
        string S;
        from_stream(S);
        int X;
        from_stream(X);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, X, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1541128390;
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
        cout << "DigitStringDiv1 (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
