#include<bits/stdc++.h>
using namespace std;

int A[20];
int cur = 17, s, x, tmp, S_x, P_x, Y_x;

void solve(int i, int j) {
    printf("+ %d %d\n", A[i], A[j]);    s = cur++;
    printf("- %d\n", A[i]);             tmp = cur++;
    printf("+ %d %d\n", A[j], tmp);     x = cur++;
    printf("C %d 0.0000000000001\n", x);x = cur++;
    printf("< %d 1000\n", x);           tmp = cur++;
    printf("S %d\n", tmp);              S_x = cur++;
    printf("< %d 154\n", S_x);          P_x = cur++;
    printf("> %d 153\n", x);            tmp = cur++;
    printf("+ %d %d\n", tmp, P_x);      Y_x = cur++;
    printf("S %d\n", Y_x);              Y_x = cur++;
    printf("C %d -0.5\n", Y_x);         Y_x = cur++;
    printf("< %d 155\n", Y_x);          Y_x = cur++;
    printf("- %d\n", P_x);              tmp = cur++;
    printf("+ %d %d\n", tmp, Y_x);      tmp = cur++;
    printf("+ %d %d\n", A[i], tmp);     A[i] = cur++;
    printf("- %d\n", A[i]);             tmp = cur++;
    printf("+ %d %d\n", s, tmp);        A[j] = cur++;
}

int main() {

    freopen("nodes9.out", "w", stdout);

    for (int i = 1; i <= 16; ++ i) {
        A[i] = i; puts("I");
    }

    for (int i = 1; i <= 16; ++ i) 
        for (int j = i+1; j <= 16; ++ j) {
            solve(i, j);
        }
    for(int i = 1; i <= 16; ++ i) printf("O %d\n", A[i]);

    return 0;
}
