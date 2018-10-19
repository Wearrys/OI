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

class MakePolygon {
    public:
        vector<int> make(int n) {
            vector<int> ans, l, r;
            if(n == 3) return (vector<int>) { 101, 201, 202 };
            if(n == 4) return (vector<int>) { 101, 201, 202, 102 };
            if(n == 5) return (vector<int>) { 101, 201, 303, 202, 102 };

            for(int i = 1; i <= 12; ++i) {
                l.pb(200 + 2 * i - 1), l.pb(100 + 2 * i);
                l.pb(100 + 2 * i + 1), l.pb(200 + 2 * i);
                for(int j = 3; j <= 25; ++j) { r.pb(j * 100 + 2 * i - 1 + (j % 2 == 0)); }
                for(int j = 25; j >= 3; --j) { r.pb(j * 100 + 2 * i + (j % 2 == 0)); }

                if((int) l.size() + (int) r.size() + 1 >= n) { l.pb(200 + 2 * i + 1); break; }
            }

            std::reverse(l.begin(), l.end());
            for(auto x : l) ans.pb(x);
            for(auto y : r) ans.pb(y);

            while((int) ans.size() > n) {
                ans.erase(max_element(ans.begin(), ans.end()));
            }

            return ans;
        }
};

// CUT begin
ifstream data("MakePolygon.sample");

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

bool do_test(int N, vector<int> __expected) {
    time_t startClock = clock();
    MakePolygon *instance = new MakePolygon();
    vector<int> __result = instance->make(N);
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
        int N;
        from_stream(N);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1539953335;
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
        cout << "MakePolygon (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
