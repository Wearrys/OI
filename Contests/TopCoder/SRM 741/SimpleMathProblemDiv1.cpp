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

class SimpleMathProblemDiv1 {

    static const int N = 500000;

    ll ans;
    ll s0[N + 5], S0[N + 5];
    ll s1[N + 5], S1[N + 5];
    int m, prime[N + 5], pcnt;

#define get_sum(x) ((x) > m ? S1[n / (x)] : s1[(x)])

    ll solve(ll n, ll p) {
        n /= p;
        ll cur = 1, res = 0;
        while(n >= cur) {
            res += (cur * p) * (std::min(n+1, cur*p) - cur);
            cur *= p;
        }
        return res;
    }
    
    public:
    long long calculate(long long n) {
        m = (int) sqrt(n + 0.5);

        for(int i = 1; i <= m; ++i) {
            s0[i] = i - 1;
            s1[i] = (ll) (2 + i) * (i - 1) / 2;
            ll t = (n / i);
            S0[i] = t - 1;
            S1[i] = (ll) (2 + t) * (t - 1) / 2;
        }

        for(int i = 2; i <= m; ++i) {
            if(s0[i] == s0[i-1]) continue;
            ans += solve(n, i);

            const ll t0 = s0[i-1], t1 = s1[i-1], p = (ll) i * i;
            const ll lim = std::min((ll) m, n / p), x = m / i, y = n / i;

            for(int j = 1; j <= x; ++j) {
                S0[j] = (S0[j] - (S0[j * i] - t0));
                S1[j] = (S1[j] - (S1[j * i] - t1) * i);
            }
            for(int j = x+1; j <= lim; ++j) {
                S0[j] = (S0[j] - (s0[y / j] - t0));
                S1[j] = (S1[j] - (s1[y / j] - t1) * i);
            }
            for(int j = m; j >= p; --j) {
                s0[j] = (s0[j] - (s0[j / i] - t0));
                s1[j] = (s1[j] - (s1[j / i] - t1) * i);
            }
        }

        for(ll p = m + 1, nxt; p <= n; p = nxt + 1) {
            nxt = n / (n / p);
            ans = ans + (n / p) * (get_sum(nxt) - get_sum(p - 1));
        }

        return ans;
    }
};

// CUT begin
ifstream data("SimpleMathProblemDiv1.sample");

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

bool do_test(long long X, long long __expected) {
    time_t startClock = clock();
    SimpleMathProblemDiv1 *instance = new SimpleMathProblemDiv1();
    long long __result = instance->calculate(X);
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
        long long X;
        from_stream(X);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(X, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1541159147;
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
        cout << "SimpleMathProblemDiv1 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
