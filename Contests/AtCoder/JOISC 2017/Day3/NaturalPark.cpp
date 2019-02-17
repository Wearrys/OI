#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include "park.h"
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1400 + 5;

int n;
static vector<int> G[MAXN];
static int que[MAXN], head, tail;
static int ask[MAXN], vis[MAXN], tag[MAXN];

void addedge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);

    if(u > v) swap(u, v);
    Answer(u, v);
}

inline bool query(int x, int y, int *p) {
    if(x > y) swap(x, y);
    return Ask(x, y, p);
}

inline bool chk(int x) {
    for(int i = 0; i < n; ++i) ask[i] = (vis[i] == 1 || i == x);
    return query(0, x, ask);
}

int calc(int x) {
    int l = 0, r = n-1;
    while(l < r) {
        int mid = (l + r + 1) >> 1;
        for(int i = 0; i < mid; ++i) ask[i] = (vis[i] != 2);
        for(int i = mid; i < n; ++i) ask[i] = (vis[i] == 1);

        ask[x] = 1;

        if(query(0, x, ask)) {
            r = mid - 1;
        } else {
            l = mid;
        }
    }
    return l;
}

void bfs(int s) {
    static int lst[MAXN], now = 0;

    head = tail = 0;
    lst[s] = ++ now;
    que[tail ++] = s;

    while(head < tail) {
        int x = que[head ++];
        for(auto y : G[x]) {
            if(tag[y] == 1 && lst[y] != now) {
                lst[y] = now;
                que[tail ++] = y;
            }
        }
    }
    return;
}

void solve(int x) {

    vis[x] = 2;
    for( ; !chk(x); solve(calc(x)));
    for(int i = 0; i < n; ++i) tag[i] = vis[i];

    for(int i = 0; i < n; ++i) {
        while(tag[i] == 1) {
            bfs(i);

            memset(ask, 0, sizeof ask);
            for(int j = 0; j < tail; ++j) ask[que[j]] = 1;
            ask[x] = 1;

            if(query(x, i, ask)) {
                int l = 0, r = tail-1;
                while(l < r) {
                    int mid = (l + r + 1) >> 1;
                    memset(ask, 0, sizeof ask);
                    for(int j = 0; j < mid; ++j) ask[que[j]] = 1;
                    ask[x] = 1;

                    if(query(i, x, ask)) {
                        r = mid - 1;
                    } else {
                        l = mid;
                    }
                }

                tag[que[l]] = 0;
                addedge(x, que[l]);
            } else {
                for(int j = 0; j < tail; ++j) tag[que[j]] = 0;
            }
        }
    }

    vis[x] = 1;
}

void Detect(int T, int N) {
    n = N;
    vis[0] = 1;

    for(int i = 1; i < n; ++i) if(!vis[i]) {
        solve(i);
    }
}
