#include "kth.h"
#define min(a, b) ((a) < (b) ? (a) : (b))

int query_kth(int n_a, int n_b, int n_c, int k) {
    int p_a = 0, p_b = 0, p_c = 0, ans;

    while(k) {
        int l = k / 3;
        if(l) --l;
        int v_a = get_a(p_a + l);
        int v_b = get_b(p_b + l);
        int v_c = get_c(p_c + l);
        int Min = min(v_a, min(v_b, v_c));

        if(v_a == Min) ans = v_a, p_a += l+1;
        else if(v_b == Min) ans = v_b, p_b += l+1;
        else ans = v_c, p_c += l+1;
        k -= l+1;
    }
    return ans;
}
