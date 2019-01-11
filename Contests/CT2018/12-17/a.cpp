#include "sort.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 550000;

int a[N + 5];
void solve(int l, int r, int k) {
    static int t[N + 5];

    if(r - l == k) {
        super_sort(a + l, k, a + l);
        return;
    }

    int m = (l + r) >> 1;
    solve(l, m, k);
    solve(m, r, k);

    int x = l, y = m, p = l;
    static int temp[N + 5], bel[N + 5];

    for(int i = l; i < m; ++i) bel[a[i]] = 0;
    for(int i = m; i < r; ++i) bel[a[i]] = 1;

    while(x < m && y < r) {
        int c = 0;
        for(int i = 0; c < (k >> 1) && (i + x) < m; ++i) { temp[c ++] = a[i + x]; }
        for(int i = 0; c < k && (i + y) < r; ++i) { temp[c ++] = a[i + y]; }
        super_sort(temp, c, temp);

        int id = bel[temp[c-1]];
        for(int i = c - 1; i >= 0; --i) if(bel[temp[i]] != id) {
            int step[2] = {0, 0};
            for(int j = 0; j <= i; ++j) {
                t[p ++] = temp[j];
                step[bel[temp[j]]] ++;
            }

            x += step[0];
            y += step[1];

            break;
        }
    }

    while(x < m) t[p ++] = a[x ++];
    while(y < r) t[p ++] = a[y ++];

    for(int i = l; i < r; ++i) a[i] = t[i];
}

void solve4(int l, int r, int k) {
    if(r - l == 32) { solve(l, r, k); return; }
    if(r - l <= k) { super_sort(a + l, r - l, a + l); return; }

    int x = l + ((r - l) >> 2);
    int m = l + ((r - l) >> 1);
    int y = r - ((r - l) >> 2);

    solve4(l, x, k);
    solve4(x, m, k);
    solve4(m, y, k);
    solve4(y, r, k);

    int p = l;
    int pos[4] = { l, x, m, y };

    static int t[N + 5];
    static int temp[N + 5], bel[N + 5];

    for(int i = l; i < x; ++i) bel[a[i]] = 0;
    for(int i = x; i < m; ++i) bel[a[i]] = 1;
    for(int i = m; i < y; ++i) bel[a[i]] = 2;
    for(int i = y; i < r; ++i) bel[a[i]] = 3;

    while(pos[0] < x || pos[1] < m || pos[2] < y || pos[3] < r) {
        int c = 0, len = (k >> 2);
        for(int i = 0; c < 1 * len && (pos[0] + i) < x; ++i) temp[c ++] = a[pos[0] + i];
        for(int i = 0; c < 2 * len && (pos[1] + i) < m; ++i) temp[c ++] = a[pos[1] + i];
        for(int i = 0; c < 3 * len && (pos[2] + i) < y; ++i) temp[c ++] = a[pos[2] + i];
        for(int i = 0; c < 4 * len && (pos[3] + i) < r; ++i) temp[c ++] = a[pos[3] + i];

        super_sort(temp, c, temp);

        int vis[4] = {0}, cnt = (pos[0] < x) + (pos[1] < m) + (pos[2] < y) + (pos[3] < r);
        for(int i = c - 1; i >= 0; --i) {
            if(!vis[bel[temp[i]]]) vis[bel[temp[i]]] = 1;

            int tot = 0;
            for(int j = 0; j < 4; ++j) if(j != bel[temp[i]] && vis[j]) { ++ tot; }

            if(tot == cnt - 1) {
                int step[4] = {0};
                for(int j = 0; j <= i; ++j) {
                    t[p ++] = temp[j];
                    step[bel[temp[j]]] ++;
                }
                for(int j = 0; j < 4; ++j) pos[j] += step[j];
                break;
            }
        }
    }

    while(pos[0] < x) t[p ++] = a[pos[0] ++];
    while(pos[1] < m) t[p ++] = a[pos[1] ++];
    while(pos[2] < y) t[p ++] = a[pos[2] ++];
    while(pos[3] < r) t[p ++] = a[pos[3] ++];

    for(int i = l; i < r; ++i) a[i] = t[i];
}

void sort(int id, int n, int k, int *res) {
    for(int i = 0; i < n; ++i) a[i] = i;
    random_shuffle(a, a + n);
    solve4(0, n, k);
    for(int i = 0; i < n; ++i) res[i] = a[i];
}
