#include "portals.h"
namespace io
{
	int F()
	{
		int n=0,F=1;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=0:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=(n<<1)+(n<<3)+ch-'0';
		return F?n:-n;
	}
	long long G()
	{
		long long n=0,F=1;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=0:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=(n<<1)+(n<<3)+ch-'0';
		return F?n:-n;
	}
}

int adjust(int N,int* a,int* b);

class grader
{
	private:
		int A[1111],B[1111];
		int a[1111],b[1111];
		int n; 
	public:
		void Inc(int i)
		{
			assert(i>=0);
			assert(i<n);
			int t=a[i];
			a[t]--;
			if(a[t]<0)a[t]+=n;
			if(a[t]>=n)a[t]-=n;
			a[i]++;
			if(a[i]<0)a[i]+=n;
			if(a[i]>=n)a[i]-=n;
		}
		void Dec(int i)
		{
			assert(i>=0);
			assert(i<n);
			int t=a[i];
			a[t]++;
			if(a[t]<0)a[t]+=n;
			if(a[t]>=n)a[t]-=n;
			a[i]--;
			if(a[i]<0)a[i]+=n;
			if(a[i]>=n)a[i]-=n;
		}
		void init()
		{
			n=io::F();
			assert(n>=1);
			assert(n<=1000);
			for(register int i=0;i<n;++i)a[i]=A[i]=io::F(),assert(a[i]>=0),assert(a[i]<n);
			for(register int i=0;i<n;++i)b[i]=B[i]=io::F(),assert(b[i]>=0),assert(b[i]<n);
		}
		int main()
		{
			init();
			int tmp=adjust(n,A,B);
			int cnt=0;
			for(register int i=0;i<n;++i)
			{
				printf("%d%c",a[i]," \n"[i==n-1]);
				if(a[i]==b[i])++cnt;
			}
			printf("%d %d\n",cnt,n);
			printf("%d\n",tmp);
			return 0;
		} 
}G;
void Inc(int x){G.Inc(x);}
void Dec(int x){G.Dec(x);}
int main()
{
	G.main();
	return 0;
}


