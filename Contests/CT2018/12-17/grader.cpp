 #include "sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


namespace grader {

#define debug(...) fprintf(stderr, __VA_ARGS__)

template <class T>
inline void swap(T &a, T &b) {
	T c = a; a = b; b = c;
}

const int MAXN = 550005, MAXK = 20;

int n, k;
int limit;
int L1, L2, L4, id;

int A[MAXN], res[MAXN];
int cmp_cnt = 0;
	
void score()
{
	exit(0);
}

void fix(int a)
{
	if (0 <= a && a < n) return;
	debug("Wrong Answer --- index is not in [0, n)");
	score();
}


void merge_sort(int *a, int L, int R)
{
	if (L >= R) return;
	int mid = (L+R)>>1;
	merge_sort(a, L, mid), merge_sort(a, mid+1, R);
	static int tmp[MAXK];
	int Lpos = L, Rpos = mid+1, top = L;
	while (Lpos <= mid && Rpos <= R) {
		if (A[a[Lpos]] <= A[a[Rpos]]) tmp[top++] = a[Lpos++];
		else tmp[top++] = a[Rpos++];
	}
	while (Lpos <= mid) tmp[top++] = a[Lpos++];
	while (Rpos <= R) tmp[top++] = a[Rpos++];
	for (int i = L; i <= R; i++)
		a[i] = tmp[i];
}

}

void super_sort(int *a, int L, int *b)
{
	using namespace grader;
	if (L > k) {
		debug("Wrong Answer --- the length of query array is too large");
		score();
	}
	cmp_cnt++;
	for (int i = 0; i < L; i++) {
		grader::fix(a[i]);
		if (a != b)
			b[i] = a[i];
	}
	merge_sort(b, 0, L-1);
}

int main() {
	using namespace grader;
    freopen("in", "r", stdin);
	assert(scanf("%d%d%d%d%d%d", &id, &n, &k, &L1, &L2, &L4) == 6);
	
	assert(n > 0);
	assert(1 <= id && id <= 3);

	static int vv[MAXN];
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
		assert(0 <= A[i] && A[i] < n);
		assert(!vv[A[i]]);
		vv[A[i]] = 1;
	}
	
	for (int i = 0; i < n; i++) {
		res[i] = i;
	}
	
	sort(id, n, k, res);
	for (int i = 0; i < n; i++) {
		if (res[i] < 0 || res[i] >= n) {
			debug("Wrong Answer --- res[%d] = %d not in [0, n)\n", i, res[i]);
			grader::score();
		}
		if (A[res[i]] != i) {
			debug("Wrong Answer --- not sorted\n");
			grader::score();
		}
	}
	debug("cmp_cnt = %d\n", cmp_cnt);
	if (cmp_cnt <= L1) grader::score();
	else if (cmp_cnt <= L2) grader::score();
	else if (cmp_cnt <= L4) grader::score();
	else grader::score();
	
	return 0;
}
