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

typedef long long ll;

const int N = 100;
const int mo = 1e9 + 7;

struct matrix {
    int v[N + 5][N + 5];

    matrix(const bool &t = 0) {
        memset(v, 0, sizeof v);
        if(t) for(int i = 0; i <= N; ++i) v[i][i] = 1;
    }
};

int n;
matrix operator * (const matrix& a, const matrix& b) {
    matrix c;
    for(int i = 0; i < (n << 1); ++i) {
        for(int j = 0; j < (n << 1); ++j) {
            for(int k = 0; k < (n << 1); ++k) {
                c.v[i][k] = (c.v[i][k] + (ll) a.v[i][j] * b.v[j][k]) % mo;
            }
        }
    }
    return c;
}

matrix operator ^ (const matrix& a, int exp) {
    matrix ans (1), t = a;
    for(; exp > 0; exp >>= 1) {
        if(exp & 1) 
            ans = ans * t;
        t = t * t;
    }
    return ans;
}

matrix trans(string p, int delta) {
    matrix tmp;

    for(int i = 0; i < n; ++i) {
        tmp.v[i][i] ++;
        tmp.v[i][i + n] ++;
        tmp.v[i][(i + n - 1) % n] ++;

        if(p[i] != p[(i + delta) % n]) {
            tmp.v[(i + 1) % n + n][i] = mo - 1;
        } 
    }
    return tmp;
}

void print(matrix x) {
    for(int j = 0; j < (n << 1); ++j) {
        printf("%d ", x.v[0][j]);
    }
    printf("\n");
}

class LongPalindromes {
    public:
    int count(int repeats, string pattern) {
        n = pattern.length();

        matrix cur;
        for(int i = 0; i < n; ++i) cur.v[0][i] = 1;
        for(int i = 0; i < n; ++i) {
            cur = cur * trans(pattern, i);
        }
        cur = cur ^ repeats;
        return cur.v[0][0];
    }
};

// CUT begin
ifstream data("LongPalindromes.sample");

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

bool do_test(int repeats, string pattern, int __expected) {
    time_t startClock = clock();
    LongPalindromes *instance = new LongPalindromes();
    int __result = instance->count(repeats, pattern);
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
        int repeats;
        from_stream(repeats);
        string pattern;
        from_stream(pattern);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(repeats, pattern, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1541055191;
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
        cout << "LongPalindromes (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
