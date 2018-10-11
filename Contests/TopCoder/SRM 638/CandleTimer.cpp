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

#define pb push_back
const int N = 200;
const int oo = 0x3f3f3f3f;

class CandleTimer {
    int n;
    set<int> s;
    int mn[N + 5];
    int dis[N + 5][N + 5];

    public:
        int differentTime(vector<int> A, vector<int> B, vector<int> len) {
            s.clear();
            n = A.size() + 1;
            vector<int> G[N + 5], leaf;
            memset(dis, oo, sizeof dis);

            for(int i = 0; i < n; ++i) dis[i][i] = 0;
            for(int i = 0; i < (int) A.size(); ++i) {
                G[A[i]].pb(B[i]); G[B[i]].pb(A[i]);
                dis[A[i]][B[i]] = dis[B[i]][A[i]] = len[i];
            }
            for(int k = 0; k < n; ++k) {
                for(int i = 0; i < n; ++i) {
                    for(int j = 0; j < n; ++j) {
                        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                    }
                }
            }

            for(int i = 0; i < n; ++i) if(G[i].size() == 1) leaf.pb(i);

            for(auto x : leaf) {
                int mx = 0;
                for(int i = 0; i < n; ++i) mx = max(mx, dis[x][i]);
                s.insert(2 * mx);

                for(auto y : leaf) {
                    for(int i = 0; i < (int) A.size(); ++i) {
                        int u = A[i], v = B[i], l = len[i];
                        if(dis[x][u] >= dis[y][u]) std::swap(u, v);
                        if(dis[x][u] + l + dis[v][y] == dis[x][y] && dis[x][u] * 2 <= dis[x][y] && dis[x][v] * 2 >= dis[x][y]) {
                            vector<int> st;
                            for(auto z : leaf) {
                                if(dis[z][u] < dis[z][v] && dis[z][u] >= dis[x][u]) st.pb(z); 
                                if(dis[z][v] < dis[z][u] && dis[z][v] >= dis[y][v]) st.pb(z);
                            }
                            
                            for(int j = 0; j < n; ++j) {
                                mn[j] = oo;
                                for(auto z : st) mn[j] = min(mn[j], dis[z][j]);
                            }

                            mx = 0;
                            for(int j = 0; j < (int) A.size(); ++j) {
                                mx = max(mx, 2 * mn[A[j]]);
                                mx = max(mx, 2 * mn[B[j]]);
                                if(std::abs(mn[A[j]] - mn[B[j]]) != len[j]) {
                                    mx = max(mx, mn[A[j]] + mn[B[j]] + len[j]);
                                }
                            }
                            s.insert(mx);
                            break;
                        }
                    }
                }
            }

            for(auto x : leaf) {
                for(auto y : leaf) {
                    int mx = 0;
                    vector<int> st;

                    for(auto z : leaf) {
                        if(dis[z][y] >= dis[x][y]) {
                            st.pb(z);
                        }
                    }
                    for(int j = 0; j < n; ++j) {
                        mn[j] = oo;
                        for(auto z : st) mn[j] = min(mn[j], dis[z][j]);
                    }

                    mx = 0;
                    for(int j = 0; j < (int) A.size(); ++j) {
                        mx = max(mx, 2 * mn[A[j]]);
                        mx = max(mx, 2 * mn[B[j]]);
                        if(std::abs(mn[A[j]] - mn[B[j]]) != len[j]) {
                            mx = max(mx, mn[A[j]] + mn[B[j]] + len[j]);
                        }
                    }
                    s.insert(mx);
                }
            }
            return (int) s.size();
        }
};

// CUT begin
ifstream data("CandleTimer.sample");

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

bool do_test(vector<int> A, vector<int> B, vector<int> len, int __expected) {
    time_t startClock = clock();
    CandleTimer *instance = new CandleTimer();
    int __result = instance->differentTime(A, B, len);
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
        vector<int> B;
        from_stream(B);
        vector<int> len;
        from_stream(len);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, len, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1539171991;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 800 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "CandleTimer (800 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
