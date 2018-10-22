#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class Subpolygon {
    static const int mo = 998244353;
    static const int MAXN = 1 << 20;

    private:
        int n;
    
        int fpm(int x, int y) {
            int res = 1;
            for(; y > 0; y >>= 1) {
                if(y & 1)
                    res = (ll) res * x % mo;
                x = (ll) x * x % mo;
            }
            return res;
        }

        void init(int m) {
            n = m;
            while(n > (n & -n)) n += (n & -n);
        }

        void dft(int *x, int ty) {
            for(int i = 0, j = 0; i < n; ++i) {
                if(i < j) std::swap(x[i], x[j]);
                for(int l = n >> 1; (j ^= l) < l; l >>= 1);
            }

            for(int l = 1; l < n; l <<= 1) {
                int wn = fpm(3, (mo - 1) / l / 2);
                if(ty == -1) wn = fpm(wn, mo - 2);

                for(int i = 0; i < n; i += (l << 1)) {
                    int w = 1;    

                    for(int j = 0; j < l; ++j) {
                        int u = x[i + j];
                        int v = (ll) w * x[i + j + l] % mo;

                        w = (ll) w * wn % mo;
                        x[i + j] = (u + v) % mo;
                        x[i + j + l] = (u - v + mo) % mo;
                    }
                }
            }

            if(ty == -1) {
                int inv = fpm(n, mo - 2);
                for(int i = 0; i < n; ++i) {
                    x[i] = (ll) x[i] * inv % mo;
                }
            }
        }

    public:

        int X[MAXN + 5], Y[MAXN + 5];
        int a[MAXN + 5], b[MAXN + 5], c[MAXN + 5], d[MAXN + 5];

        int sumOfAreas(int N) {
            init(N << 3 | 5);

            for(int i = 1; i <= N; ++i) {
                X[i] = (X[i - 1] + N - i) % mo;
                Y[i] = (Y[i - 1] + i) % mo;
            }
            for(int i = 1; i <= N; ++i) {
                X[N + i] = (X[N + i - 1] + mo - i) % mo;
                Y[N + i] = (Y[N + i - 1] + N - i) % mo;
            }
            for(int i = 1; i <= N; ++i) {
                X[2*N + i] = (X[2*N + i - 1] + mo - N + i) % mo;
                Y[2*N + i] = (Y[2*N + i - 1] + mo - i) % mo;
            }
            for(int i = 1; i <= N; ++i) {
                X[3*N + i] = (X[3*N + i - 1] + i) % mo;
                Y[3*N + i] = (Y[3*N + i - 1] + mo - N + i) % mo;
            }

            for(int i = 1; i <= 4*N; ++i) a[4 * N - i] = X[i], b[i] = Y[i], c[4 * N - i] = Y[i], d[i] = X[i];

            dft(a, +1), dft(b, +1), dft(c, +1), dft(d, +1);
            for(int i = 0; i < n; ++i) a[i] = (ll) a[i] * b[i] % mo, c[i] = (ll) c[i] * d[i] % mo;
            dft(a, -1), dft(c, -1);
            
            int ans = 0;
            for(int i = 8*N - 1; i > 4*N; --i) {
                int l = i - 4*N + 1, r = 4*N - l;
                l -= 2;
                ans = (ans + (ll) (fpm(2, l) - 1) * (c[i] - a[i] + mo)) % mo;
                ans = (ans + (ll) (fpm(2, r) - 1) * (a[i] - c[i] + mo)) % mo;
            }
            return (ll) ans * fpm(2, mo - 2) % mo;
        }
};

// CUT begin
ifstream data("Subpolygon.sample");

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

bool do_test(int n, int __expected) {
    time_t startClock = clock();
    Subpolygon *instance = new Subpolygon();
    int __result = instance->sumOfAreas(n);
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
        int n;
        from_stream(n);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1540217682;
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
        cout << "Subpolygon (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
