#include "Broken_device_lib.h"
#include <bits/stdc++.h>

using std::pair;
using std::string;
using std::vector;

typedef long long ll;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb(a) push_back(a)
#define mp(a, b) std::make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)

template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;

string procStatus() {
    std::ifstream t("/proc/self/status");
    return string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}

template <typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

bool mark[200];

const int table[8][2] = { 
    { 1, 0 }, { 2, 1 }, { 4, 0 }, { 4, 2 }, 
    { 2, 0 }, { 4, 1 }, { 2, 1 }, { 4, 3 }
};

inline void set(int x, int a, int b, int c) {
    Set(x, a);
    Set(x + 1, b);
    Set(x + 2, c);
}

void Anna(int N, ll x, int K, int P[]) {
    memset(mark, 0, sizeof mark);
    for(int i = 0; i < K; ++i) mark[P[i]] = true; 
    for(int i = 0; i < N; i += 3) {
        int temp = mark[i] + mark[i+1] + mark[i+2];
        
        if(temp >= 2) { set(i, 0, 0, 0); continue; } 
        if(temp == 1) {
            if(mark[i + 1]) { ((x & 1ll) ? set(i, 0, 0, 1) : set(i, 1, 0, 0)); x >>= 1ll; }
            if(mark[i + 2]) { ((x & 1ll) ? set(i, 1, 1, 0) : set(i, 1, 0, 0)); x >>= 1ll; }
            if(mark[i]) {
                if(x & 1ll) { set(i, 0, 0, 1), x >>= 1ll; }
                else { ((x & 3ll) ? set(i, 0, 1, 1) : set(i, 0, 1, 0)); x >>= 2; }
            }
        } 
        if(temp == 0) {
            ll t = x & 3ll; x >>= 2;
            if(t == 0) set(i, 0, 1, 0);
            if(t == 1) set(i, 1, 0, 1);
            if(t == 2) set(i, 0, 1, 1);
            if(t == 3) set(i, 1, 1, 1);
        }
    }
}

ll Bruno(int N, int A[]) {
    ll ans = 0, bit = 1;
    for(int i = 0; i < N; i += 3) {
        int x = (A[i] << 1 | A[i + 1]) << 1 | A[i + 2];
        ans = ans + bit * table[x][1]; 
        bit = bit * table[x][0];
    }
    return ans;
}
