#include "testlib.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define Rep(i,a) for(int i = 0; i < a; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
typedef long long LL;
using namespace std;
int C[int(1e6) + 10], state[1010];
string s[16];
int main(int argc, char * argv[]) {
	registerTestlibCmd(argc, argv);
	Rep(i,(1 << 16)) C[i] = C[i >> 1] + (i & 1);
	int T = inf.readInt(1, 4);
	if (T <= 2) {
		int n = 15;
		Rep(i,n) s[i] = ouf.readString("[0-1]{16384}");
		int flaw = 0;
		Rep(S,(1 << n)) {
			int tot = 0;
			Rep(i,n) {
				int s1 = ((S >> (i + 1)) << i) | (S & ((1 << i) - 1));
				if (s[i][s1] == '0') tot--; else tot++;
			}
			if ((tot > 0) != (C[S] % 2 == 1)) flaw++;
		}
		stringstream fl; fl << flaw;
		string num; fl >> num;

		if (T == 1) {
			if (flaw >= 7000) quitp((double).0, "too many (" + num + ") flaws");
			else quitp((double)1.0, "Accepted " + num + " flaws");
		} else {
			if (flaw >= 2100) quitp((double).0, "too many (" + num + ") flaws");
			else quitp((double)1.0, "Accepted " + num + " flaws");
		}
	} else if (T == 3) {
		int n = 15, flaw = 0;
		static int s[17][16384 + 17];
		Rep(i,n) Rep(j,(1 << (n - 1))) s[i][j] = ouf.readInt(-int(1e8), int(1e8));
		Rep(S,(1 << n)) {
			int tot = 0;
			Rep(i,n) {
				int s1 = ((S >> (i + 1)) << i) | (S & ((1 << i) - 1));
				tot += s[i][s1];
			}
			if (tot == 0) flaw++;
			else if ((tot > 0) != (C[S] % 2 == 1)) flaw++;
		}
		stringstream fl; fl << flaw;
		string num; fl >> num;
		if (flaw >= 3) quitp((double).0, "too many (" + num + ") flaws");
		else quitp((double)1.0, "Accepted " + num + " flaws");
	} else if (T == 4) {
		static int s[1010][4096 + 7];
		int n = 12, k = 7, l = 0, flaw = 0;
		Rep(i,(1 << n)) if (C[i] == k) l++, state[l] = i;
		rep(i,1,l) Rep(j,(1 << k)) s[i][j] = ouf.readInt(-int(1e8), int(1e8));
		Rep(S,(1 << n)) {
			LL tot = 0;
			rep(i,1,l) {
				int c = 0, s1 = 0;
				Rep(j,n) if (state[i] >> j & 1) {
					s1 |= (S >> j & 1) << c;
					c++; 
				}
				tot += s[i][s1];
			}
			if (tot == 0) flaw++;
			else if ((tot > 0) != (C[S] % 2 == 1)) flaw++;
		}
		stringstream fl; fl << flaw;
		string num; fl >> num;
		if (flaw >= 80) quitp((double).0, "too many (" + num + ") flaws");
		else quitp((double)1.0, "Accepted " + num + " flaws");
	}
	return 0;
}
