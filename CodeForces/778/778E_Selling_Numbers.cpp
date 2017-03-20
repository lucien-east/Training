#include <iostream>
#include <string>
#include <ios>
#define N (1000)

using namespace std;

string B[N];
unsigned int cost[10];
bool carry[10][N];
unsigned int digit_cnt[10];
unsigned int currnet_max_digit_cnt[10];

long long price()
{
	long long sum = 0;
	for(int i=0; i<10; ++i)
		sum += (cost[i]*digit_cnt[i]);

	return sum;
}

unsigned int max_strlen(const unsigned int &n)
{
	unsigned int max_len = 0;
	for(int i=0; i<n; ++i) {
		if(max_len < B[i].size())
			max_len = B[i].size();
	}

	return max_len;
}

void update_digit_cnt()
{

}

long long max_cost(const string &A, const unsigned int &n)
{
	long long tmp_cost;
	long long max = 0;
	long long current_price[10];
	unsigned int max_len;
	string ans_A = A;

	max_len = max_strlen(n);
	for(int pos_B=0, pos_A=A.size()-1;
		pos_B<max_len || pos_A>=0;
		++pos_B, --pos_A)
	{
		/* pos_A: the least significant digit
		 * pos_B: the most significant digit */
		for(int i=0; i<n; ++i) {
			/* rev_pos_B: Begin from the least significant digit of B[i] */
			int rev_pos_B = (int) B[i].size() - pos_B - 1;
			const char *tmp_B = B[i].c_str();

			if(rev_pos_B>=0 && pos_A >=0) {
				/* A[pos_A] + B[i][rev_pos_B] + carry */

			}
			else if(rev_pos_B<0 && pos_A>=0) {
				/* A is longer than B[i]: A[pos_A] + carry */

			}
			else if(rev_pos_B>=0 && pos_A <0) {
				/* B[i] is longer than A: B[i][rev_pos_B] + carry */

			}

		}
	}

	return max;
}

int main()
{
	ios_base::sync_with_stdio(false);

	string A;
	unsigned int n;

	cin >> A >> n;

	for(int i=0; i<n; ++i)
		cin >> B[i];

	for(int i=0; i<10; ++i)
		cin >> cost[i];

	cout << "MAX = " << max_cost(A, n) << '\n';

	return 0;
}
