#include <bits/stdc++.h>

using namespace std;

#define N 1010
#define oo (1<<30)

unsigned int n;
char A[N+1];
char B[N][N+1];
int c[10];

unsigned int len_A;
unsigned int len_B[N];
int dp[N][N];
pair<int, int> ord[N];
int magic = 1006;


void init();
void max_cost();

int main()
{
	ios_base::sync_with_stdio(false);

	cin >> A >> n;
	for(int i=0; i<n; ++i)
		cin >> B[i];

	for(int i=0; i<10; ++i)
		cin >> c[i];

	init();
	max_cost();

	cout << dp[magic+1][0] << '\n';

	return 0;
}

void init()
{
	len_A = strlen(A);
	reverse(A, A+len_A);
	for(int i=len_A; i<N+1; ++i) A[i] = '0';

	for(int i=0; i<n; ++i) {
		len_B[i] = strlen(B[i]);
		reverse(B[i], B[i]+len_B[i]);
		for(int j=len_B[i]; j<N+1; ++j) B[i][j] = '0';
	}


	for(int i=0; i<N; ++i)
		for(int j=0; j<N; ++j)
			dp[i][j] = -oo;

	dp[0][0] = 0;

	for(int i=0; i<N; ++i)
		ord[i] = make_pair(0, i);

	return;
}

void max_cost()
{
	int val[N];
	unsigned int max_len[N];

	for(int i=0; i<=magic; ++i) {
		int a_start=0, a_end=9;
		if(i==len_A-1) a_start = 1;
		if(A[i] != '?') a_start = a_end = A[i]-'0';

		for(int j=0; j<n; ++j) {
			val[j] = B[ord[j].second][i]-'0';
			max_len[j] = max(len_A, len_B[ord[j].second]);
		}

		for(int k=a_start; k<=a_end; ++k) {
			int carry=0, cost=0;
			for(int j=0; j<n; ++j) {
				if(val[j]+k >9) carry++;
				if(i<max_len[j]) cost +=c[(val[j]+k)%10];
			}
			for(int j=0; j<n; ++j) {
				dp[i+1][carry] = max(dp[i+1][carry], dp[i][j]+cost);

				if(val[j]+k >9) carry--;
				if(i<max_len[j]) cost -=c[(val[j]+k)%10];
				if(val[j]+k+1 >9) carry++;
				cost +=c[(val[j]+k+1)%10];
			}

			dp[i+1][carry] = max(dp[i+1][carry], dp[i][n]+cost);
		}

		for(int j=0; j<n; ++j)
			ord[j].first = val[j]*(n+1)+n-j;

		sort(ord, ord+n);
		reverse(ord, ord+n);
	}

	return;
}
