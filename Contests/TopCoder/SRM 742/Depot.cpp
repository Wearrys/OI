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
#include <bits/stdc++.h>

using namespace std;

template <typename T> inline bool chkmin(T& a, T b) {
    return a > b ? a = b, 1 : 0;
}

vector<int> get(string str) {
    int x = 0;
    vector<int> res;
    for(int i = 0; i < (int) str.length(); ++i) {
        if(isdigit(str[i])) {
            x = x * 10 + str[i] - '0';
        } else {
            res.push_back(x), x = 0;
        }
    } 
    res.push_back(x);
    return res;
}

const int N = 20;
const int M = 300000;
const int oo = 0x3f3f3f3f;

int n, q;
int f[M + 5][N + 5];
vector<int> it[N + 5];

class Depot {

    public:
        int countPositive(vector<string> arrivals, vector<string> queries) {
            n = (int) arrivals.size();

            memset(f, 0x3f, sizeof f);
            f[0][0] = 0;

            for(int i = 0; i < n; ++i) it[i] = get(arrivals[i]);
            for(int i = 0; i <= M; ++i) {
                for(int j = 0; j < n; ++j) if(f[i][j] != oo && i + it[j][3] <= M) {
                    chkmin(f[i][j+1], f[i][j]);
                    long long ed = it[j][0] + 1ll * (it[j][2] - 1) * it[j][1];
                    if(ed < f[i][j]) continue;
                    int nxt = max<int>(it[j][0], ed - (ed - f[i][j]) / it[j][1] * it[j][1]);
                    chkmin(f[i + it[j][3]][j + 1], nxt);
                }

                if(f[i][n] != oo) {
                    for(int j = 0; j < n; ++j) if(i + it[j][3] <= M) {
                        long long ed = it[j][0] + 1ll * (it[j][2] - 1) * it[j][1];
                        if(ed <= f[i][n]) continue;
                        int nxt = max<int>(it[j][0], ed - (ed - f[i][n] - 1) / it[j][1] * it[j][1]);
                        chkmin(f[i + it[j][3]][j + 1], nxt);
                    }
                }
            }

            function<int(int, int)> query = [&] (int d, int s) {
                return f[s][n] <= d;
            };

            int ans = 0;
            q = (int) queries.size();
            for(int i = 0; i < q; ++i) {
                vector<int> t = get(queries[i]);

                if(t.size() == 2) {
                    ans += query(t[0], t[1]);
                } else {
                    for(int j = 0; j < t[6]; ++j) {
                        ans += query((t[0] + j*t[2] - 1) % t[3] + 1, (t[1] + j*t[4] - 1) % t[5] + 1);
                    }
                }
            }
            return ans;
        }
};

// CUT begin
ifstream data("Depot.sample");

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

bool do_test(vector<string> arrivals, vector<string> queries, int __expected) {
    time_t startClock = clock();
    Depot *instance = new Depot();
    int __result = instance->countPositive(arrivals, queries);
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
        vector<string> arrivals;
        from_stream(arrivals);
        vector<string> queries;
        from_stream(queries);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(arrivals, queries, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1545884152;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Depot (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
