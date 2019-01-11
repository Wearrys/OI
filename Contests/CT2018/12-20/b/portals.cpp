#include "portals.h"
#include <bits/stdc++.h>

using namespace std;

int adjust(int n, int *a, int *b) {

    int x = 0, y = 0;
    bool f1 = 1, f2 = 1;

    for(int i = 0; i < n; ++i) {
        f1 &= (a[i] == i); x += a[i]; 
        f2 &= (b[i] == i); y += b[i];
    }

    if((f1 && !f2) || (x % n != y % n)) return -1;

#define lst(x) (x == 0 ? n - 1 : x - 1)
#define nxt(x) (x == n - 1 ? 0 : x + 1)

    auto inc = [&] (int x) { Inc(x); a[a[x]] = lst(a[a[x]]); a[x] = nxt(a[x]); };
    auto dec = [&] (int x) { Dec(x); a[a[x]] = nxt(a[a[x]]); a[x] = lst(a[x]); };

    for(int i = 0; i < n; ++i) if(a[i] ^ i) {
        while(a[i] != lst(i)) inc(i);

        for(int j = nxt(i); j != b[i]; j = nxt(j)) b[j] = nxt(b[j]);
        for(int j = lst(i); j != nxt(i); j = lst(j)) {
            while(nxt(a[j]) ^ b[j]) dec(i), inc(i);
            dec(i);
        }
        for(int j = nxt(i); j != b[i]; j = nxt(j)) inc(i);
        break;
    }

	return 0;
}
