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

struct node {
    int h, m, s;

    void add(int _h, int _m, int _s) {
        h += _h, m += _m, s += _s;
        if(s >= 60) m += s / 60, s %= 60; else if(s < 0) s += 60, -- m;
        if(m >= 60) h += m / 60, m %= 60; else if(m < 0) m += 60, -- h;
    }

    bool operator < (const node& rhs) const {
        if(h != rhs.h) return h < rhs.h;
        if(m != rhs.m) return m < rhs.m;
        if(s != rhs.s) return s < rhs.s;
        return false;
    }
};

string trans(int h, int m, int s) {
    h %= 24;
    string res = "";
    int x = h % 10, y = (h / 10) % 10;
    res = res + char(y + '0') + char(x + '0') + ":";
    x = m % 10, y = (m / 10) % 10;
    res = res + char(y + '0') + char(x + '0') + ":";
    x = s % 10, y = (s / 10) % 10;
    res = res + char(y + '0') + char(x + '0');
    return res;
}

vector<node> add, del;

class ForumPostEasy {

    public:
        string getCurrentTime(vector<string> exactPostTime, vector<string> showPostTime) {
            add.clear();
            del.clear();
            int n = exactPostTime.size();
            node lim = (node) { 48, 0, 0 };

            for(int i = 0; i < n; ++i) {
                int h, m, s, t;
                sscanf(exactPostTime[i].c_str(), "%d:%d:%d", &h, &m, &s);

                node tmp = (node) { h, m, s };

                if(showPostTime[i][0] == 'f') {
                    add.pb(tmp); tmp.add(0, 0, 59); del.pb(tmp);

                    tmp.add(24, 0, 0);
                    if(tmp < lim) { del.pb(tmp); tmp.add(0, 0, -59); add.pb(tmp); }
                } else {
                    sscanf(showPostTime[i].c_str(), "%d", &t);
                    for(auto c : showPostTime[i]) if(isalpha(c)) {
                        if(c == 'm') {
                            tmp.add(0, t, 0); add.pb(tmp);
                            tmp.add(0, 0, 59); del.pb(tmp);

                            tmp.add(24, 0, 0);
                            if(tmp < lim) { del.pb(tmp); tmp.add(0, 0, -59); add.pb(tmp); }
                        } else {
                            tmp.add(t, 0, 0); add.pb(tmp);
                            tmp.add(0, 59, 59); del.pb(tmp);
                            tmp.add(24, 0, 0);
                            if(tmp < lim) { del.pb(tmp); tmp.add(0, -59, -59); add.pb(tmp); }
                        }
                        break;
                    }
                }
            }

            string res = "impossible";

            std::sort(add.begin(), add.end());
            std::sort(del.begin(), del.end());

            int x = 0, y = 0, cnt = 0;
            for(int i = 0; i < 48; ++i) {
                for(int j = 0; j < 60; ++j) {
                    for(int k = 0; k < 60; ++k) {
                        while (x < (int) add.size() && add[x].h == i && add[x].m == j && add[x].s == k) {
                            ++ x;
                            ++ cnt;
                        }

                        if(cnt == n) {
                            string tmp = trans(i, j, k);
                            if(res[0] == 'i' || tmp < res) res = tmp;
                        }

                        while (y < (int) del.size() && del[y].h == i && del[y].m == j && del[y].s == k) {
                            ++ y;
                            -- cnt;
                        }
                    }
                }
            }
            return res;
        }
};

// CUT begin
ifstream data("ForumPostEasy.sample");

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

bool do_test(vector<string> exactPostTime, vector<string> showPostTime, string __expected) {
    time_t startClock = clock();
    ForumPostEasy *instance = new ForumPostEasy();
    string __result = instance->getCurrentTime(exactPostTime, showPostTime);
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
        vector<string> exactPostTime;
        from_stream(exactPostTime);
        vector<string> showPostTime;
        from_stream(showPostTime);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(exactPostTime, showPostTime, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1539219358;
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
        cout << "ForumPostEasy (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
