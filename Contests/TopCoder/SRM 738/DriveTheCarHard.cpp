#include <bits/stdc++.h>
using namespace std;

class DriveTheCarHard {
    public:
        int findMinimumFuel(int total_time, int distance) {
            int *dp = new int[distance + 1];

            if(total_time >= 300) {
                int ans = 0;
                while(distance > 0) {
                    ++ ans;
                    distance -= min(distance, total_time);
                    -- total_time;
                }
                return ans;
            }

            for(int i = 1; i <= distance; ++i) 
                dp[i] = 0x3f3f3f3f;

            for(int i = total_time; i > 0; --i) {
                for(int j = distance - i; j >= 0; --j) {
                    for(int k = 1; j + k * i <= distance && dp[j] + k*k < dp[j + k * i]; ++k) {
                        dp[j + k * i] = dp[j] + k * k;
                    }
                }
            }

            return dp[distance];
        }
};

// CUT begin
ifstream data("DriveTheCarHard.sample");

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

bool do_test(int total_time, int distance, int __expected) {
    time_t startClock = clock();
    DriveTheCarHard *instance = new DriveTheCarHard();
    int __result = instance->findMinimumFuel(total_time, distance);
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
        int total_time;
        from_stream(total_time);
        int distance;
        from_stream(distance);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(total_time, distance, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1542113024;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "DriveTheCarHard (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
