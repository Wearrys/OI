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

const int N = 10;

class ShadowSculpture {
    int n;
    bool pro[N + 5][N + 5][N + 5], vis[N + 5][N + 5][N + 5];

    public:
    void dfs(int x, int y, int z) {
        if(x < 0 || x >= n || y < 0 || y >= n || z < 0 || z >= n) return;

        if(pro[x][y][z]) {
            vis[x][y][z] = true;
            pro[x][y][z] = false;

            dfs(x + 1, y, z);
            dfs(x - 1, y, z);
            dfs(x, y + 1, z);
            dfs(x, y - 1, z);
            dfs(x, y, z + 1);
            dfs(x, y, z - 1);
        }
    }
    bool chk(vector<string> XY, vector<string> YZ, vector<string> ZX) {
        for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) {
            bool res = false;
            for(int k = 0; k < n; ++k) res |= vis[i][j][k];
            if(res != (XY[i][j] == 'Y')) return false;
        }
        for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) {
            bool res = false;
            for(int k = 0; k < n; ++k) res |= vis[k][i][j];
            if(res != (YZ[i][j] == 'Y')) return false;
        }
        for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) {
            bool res = false;
            for(int k = 0; k < n; ++k) res |= vis[j][k][i];
            if(res != (ZX[i][j] == 'Y')) return false;
        }
        return true;
    }
    string possible(vector<string> XY, vector<string> YZ, vector<string> ZX) {
        n = XY.size();
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                for(int k = 0; k < n; ++k) {
                    pro[i][j][k] = (XY[i][j] == 'Y' && YZ[j][k] == 'Y' && ZX[k][i] == 'Y');
                }
            }
        }

        if(chk(XY, YZ, ZX)) return "Possible";
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                for(int k = 0; k < n; ++k) if(pro[i][j][k]) {
                    memset(vis, 0, sizeof vis);
                    dfs(i, j, k);
                    if(chk(XY, YZ, ZX)) return "Possible";
                }
            }
        }
        return "Impossible";
    }
};

// CUT begin
ifstream data("ShadowSculpture.sample");

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

bool do_test(vector<string> XY, vector<string> YZ, vector<string> ZX, string __expected) {
    time_t startClock = clock();
    ShadowSculpture *instance = new ShadowSculpture();
    string __result = instance->possible(XY, YZ, ZX);
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
        vector<string> XY;
        from_stream(XY);
        vector<string> YZ;
        from_stream(YZ);
        vector<string> ZX;
        from_stream(ZX);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(XY, YZ, ZX, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1539158634;
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
        cout << "ShadowSculpture (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
