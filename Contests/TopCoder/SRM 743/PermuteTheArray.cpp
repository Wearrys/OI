#include <bits/stdc++.h>

using namespace std;

const int N = 1000;

class PermuteTheArray {
    public:
        int n, m, fa[N + 5];
        int findset(int x) { return fa[x] == x ? x : fa[x] = findset(fa[x]); }

        int cnt[2];
        bool vis[N + 5];
        pair<int, int> items[N + 5];

        void set(int x, bool ty) {
            for(int i = 0; i < (n << 1); ++i) if(findset(i) == findset(x)) {
                if(!vis[i] && ty) -- cnt[i & 1]; 
                if(vis[i] && !ty) ++ cnt[i & 1];
                vis[i] = ty;
            }
        }

        bool chk(int x, int c) {
            vector<int> vec;

            if(vis[x << 1 | c]) return true;
            if(vis[x << 1 | (c ^ 1)]) return false;

            set(x << 1 | c, true);

            int c0 = cnt[0], c1 = cnt[1];
            for(int i = 0; i < (n << 1); ++i) 
                if(!vis[i] && !vis[i ^ 1] && findset(i) == i) { 
                    vec.push_back(i);
                }
            
            map <pair<int, int>, bool> f, g;
            f[make_pair(0, 0)] = true;

            for(auto rt : vec) {
                if(items[rt].first > items[rt].second || (items[rt].first == items[rt].second && (rt&1))) {
                    g.clear();    
                    for(auto t : f) {
                        g[make_pair(t.first.first + items[rt].first, t.first.second + items[rt].second)] = true;
                        g[make_pair(t.first.first + items[rt ^ 1].first, t.first.second + items[rt ^ 1].second)] = true;
                    }
                    swap(f, g);
                }
            }

            set(x << 1 | c, false);
            return f[make_pair(c0, c1)];
        }

        vector<int> getPermutation(vector<int> A, vector<int> x, vector<int> y, vector<int> d) {
            vector<int> res, a[2];
            n = A.size(), m = x.size();
            for(int i = 0; i < (n << 1); ++i) fa[i] = i, vis[i] = 0;

            for(int i = 0; i < n; ++i) a[A[i] % 2].push_back(A[i]);
            for(int i = 0; i < m; ++i) {
                if(d[i]) {
                    fa[findset(x[i] << 1)] = findset(y[i] << 1 | 1);
                    fa[findset(y[i] << 1)] = findset(x[i] << 1 | 1);
                } else {
                    fa[findset(x[i] << 1)] = findset(y[i] << 1);
                    fa[findset(x[i] << 1 | 1)] = findset(y[i] << 1 | 1);
                }
            }

            cnt[0] = a[0].size();
            cnt[1] = a[1].size();

            for(int i = 0; i < n; ++i) { if(findset(i << 1) == findset(i << 1 | 1)) return res; }

            for(int i = 0; i < (n << 1); ++i) if(findset(i) == i) {
                int c0 = 0, c1 = 0;
                for(int j = 0; j < (n << 1); ++j) if(findset(j) == i) { if(j & 1) ++ c1; else ++ c0; }
                for(int j = 0; j < (n << 1); ++j) if(findset(j) == i) { items[j] = make_pair(c0, c1); }
            }

            a[0].push_back(INT_MAX);
            a[1].push_back(INT_MAX);

            sort(a[0].begin(), a[0].end(), greater<int>());
            sort(a[1].begin(), a[1].end(), greater<int>());

            if(!chk(0, 0) && !chk(0, 1)) { return res; }

            for(int i = 0; i < n; ++i) {
                int c = (a[0].back() < a[1].back()) ? 0 : 1;

                if(chk(i, c)) {
                    res.push_back(a[c].back());
                    set(i << 1 | c, true), a[c].pop_back();
                } else {
                    res.push_back(a[c ^ 1].back());
                    set(i << 1 | (c ^ 1), true), a[c ^ 1].pop_back();
                }
            }

            return res;
        }
};

// CUT begin
ifstream data("PermuteTheArray.sample");

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

bool do_test(vector<int> A, vector<int> x, vector<int> y, vector<int> d, vector<int> __expected) {
    time_t startClock = clock();
    PermuteTheArray *instance = new PermuteTheArray();
    vector<int> __result = instance->getPermutation(A, x, y, d);
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        vector<int> d;
        from_stream(d);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, x, y, d, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1547173893;
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
        cout << "PermuteTheArray (800 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
