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

const int dx0[] = { 0, 0, 1, -1, -1, 0 };
const int dy0[] = { -1, 1, 0, 0, 0, -1 };
const int dx1[] = { -1, 1, 0, 0, 1, 0 };
const int dy1[] = { 0, 0, -1, 1, 0, 1 };

class BoardCoveringDiv1 {
    static const int N = 50;

    public:

    int lim[4];
    int col[N * N + 5];
    vector<string> result;
    vector<int> adj[N * N];
    int ans[N + 5][N + 5], tot;

    int n, m;

    int idx(int x, int y) {
        if(x < 0 || x >= n || y < 0 || y >= m) 
            return -1;
        return x * m + y;
    }

    bool dfs(int S) {
        if(S == (1 << (n * m)) - 1)
            return true;

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                for(int t = 0; t < 6; ++t) {
                    int i0 = i + dx0[t], j0 = j + dy0[t];
                    int i1 = i + dx1[t], j1 = j + dy1[t];
                    int A = idx(i0, j0), B = idx(i1, j1);
                    int st = (1 << idx(i, j)) | 1 << A | 1 << B;

                    if(A >= -1 && B >= -1 && (S & st) == 0) {

                        ans[i + lim[0]][j + lim[2]] = 
                        ans[i0+ lim[0]][j0+ lim[2]] = 
                        ans[i1+ lim[0]][j1+ lim[2]] = ++ tot;

                        if(dfs(S | st)) {
                            return true; 
                        }
                        -- tot;
                    }
                }
            }
        }
        return false;
    }

    void color(int N) {
        const int dx[] = { 0, 0, -1, 1 };
        const int dy[] = { 1, -1, 0, 0 };

        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                // cout << ans[i][j] << ' ';

                for(int d = 0; d < 4; ++d) {
                    int ni = i + dx[d], nj = j + dy[d];
                    if(ni < 0 || ni >= N || nj < 0 || nj >= N) continue;

                    adj[ans[i][j]].push_back(ans[ni][nj]);
                }
            }
            // cout << endl;
        }

        memset(col, -1, sizeof col);
        for(int i = 1; i <= tot; ++i) {
            int st = 0;
            for(auto c : adj[i]) if(col[c] != -1) {
                st |= 1 << col[c]; 
            }
            for(int c = 0; c < 10; ++c) if(!(st >> c & 1)) {
                col[i] = c;
            }
        }
        for(int i = 0; i < N; ++i) {
            string tmp = "";
            for(int j = 0; j < N; ++j) {
                tmp += ans[i][j] ? char(col[ans[i][j]] + '0') : '#';
            }
            result.push_back(tmp);
        }
    }

    vector<string> make(int N, int R, int C) {
        if(N % 3 == 0)
            return vector<string>();

        lim[0] = lim[2] = 0;
        lim[1] = lim[3] = N - 1;

        while(R >= lim[0] + 3) {
            for(int j = lim[2]; j < lim[3]; ++j) {
                ++ tot;
                for(int i = lim[0]; i < lim[0] + 3; ++i) { ans[i][j] = tot; }
            } lim[0] += 3;
        }
        while(lim[1] - R >= 3) {
            for(int j = lim[2]; j < lim[3]; ++j) {
                ++ tot;
                for(int i = lim[1]; i > lim[1] - 3; --i) { ans[i][j] = tot; }
            } lim[1] -= 3;
        }
        while(C >= lim[2] + 3) {
            for(int i = lim[0]; i < lim[1]; ++i) {
                ++ tot;
                for(int j = lim[2]; j < lim[2] + 3; ++j) { ans[i][j] = tot; }
            } lim[2] += 3;
        }
        while(lim[3] - C >= 3) {
            for(int i = lim[0]; i < lim[1]; ++i) {
                ++ tot;
                for(int j = lim[3]; j > lim[3] - 3; --j) { ans[i][j] = tot; }
            } lim[3] -= 3;
        }

        n = lim[1] - lim[0] + 1, m = lim[3] - lim[2] + 1;
        dfs(1 << idx(R - lim[0], C - lim[2]));

        color(N);
        return result;
    }
};

// CUT begin
ifstream data("BoardCoveringDiv1.sample");

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

bool do_test(int N, int R, int C, vector<string> __expected) {
    time_t startClock = clock();
    BoardCoveringDiv1 *instance = new BoardCoveringDiv1();
    vector<string> __result = instance->make(N, R, C);
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
        int R;
        from_stream(R);
        int C;
        from_stream(C);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, R, C, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1541144290;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BoardCoveringDiv1 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
