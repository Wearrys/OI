#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb push_back

template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;
const int maxn = 2e6 + 10;
const int mod = 1e9 + 7;

template<typename T> T read() {
	T n(0), f(1);
	char ch = getchar();
	for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48;
	return n * f;
}

int n;
char S[maxn];
int nxt[maxn], nxt2[maxn], cnt[maxn], cnt2[maxn];

void Solve() {
    cnt[0] = cnt[1] = 0;
    nxt[0] = nxt[1] = 0;

    for(int i = 1; i < n; i++) {
        int j = nxt[i];
        while(j && S[j] != S[i]) j = nxt[j];

        if(S[j] == S[i]) {
            nxt[i+1] = j+1;
            cnt[i+1] = cnt[j+1] + 1;
        }else nxt[i+1] = cnt[i+1] = 0;
    }

    LL ans = 1;

    nxt2[0] = nxt2[1] = 0;
    cnt2[0] = cnt2[1] = 0;
    for(int i = 1; i < n; i++) {
        int j = nxt2[i];
        while(j && (S[j] != S[i] || ((j+1)*2 > i+1)))
            j = nxt[j];
        
        if(S[j] == S[i] && (j+1)*2 <= i+1) {
            nxt2[i+1] = j+1;
            cnt2[i+1] = cnt[j+1] + 1;
        }else nxt2[i+1] = cnt2[i+1] = 0;
    }

    for(int i = 1; i <= n; i++) ans = ans * (cnt2[i]+1) % mod;
    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
#endif

    for(int T = read<int>(); T; T--) {
        scanf("%s", S);
        n = strlen(S); 

        Solve();
    }
    return 0;
}
