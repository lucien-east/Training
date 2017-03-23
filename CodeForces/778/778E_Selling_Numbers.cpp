#include <iostream>
#include <string>
#include <ios>
#define N (1000)

using namespace std;

string B[N];
unsigned int cost[10];
bool carry[10][N];
unsigned int previous_digit_cnt[10][10];
unsigned int current_digit_cnt[10][10];		// record '?': 0-9 and its digit cnt
unsigned int currnet_max_digit_cnt[10];

long long price(const unsigned int *digit_cnt_table)
{
	long long sum = 0;
	for(int i=0; i<10; ++i)
		sum += (cost[i]*digit_cnt_table[i]);

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

void print_digit_cnt(const unsigned int digit_cnt_table[][10], const int &d)
{
	// Debug use
	cout << "The digit count table: d = " << d << "\n";
	for(int i=0; i<10; ++i)
		cout << "[" << i << "]:" << digit_cnt_table[d][i] << '\n';
	cout << "\n\n\n";
}

void init_table(int *table, const int &size)
{
	for(int i=0; i<size; ++i)
		table[i] = 0;
}

long long max_cost(const string &A, const unsigned int &n)
{
	long long tmp_cost;
	long long max = 0;
	long long current_price[10];
	long long previous_price[10];
	unsigned int max_len;
	int a;
	string ans_A = A;

	max_len = max_strlen(n);
	for(int pos_B=0, pos_A=A.size()-1;
		pos_B<max_len || pos_A>=0;
		++pos_B, --pos_A)
	{
		for(int cur_d=0; cur_d<=9; ++cur_d) {

			for(int pre_d=0; pre_d<=9; ++pre_d) {

				for(int i=0; i<n; ++i) {
					/***
					 * pos_A: the least significant digit of A
					 * pos_B: the most significant digit of B[i]
					 * rev_B: the least significant digit of B[i]
					 ***/
					int rev_B = (int) B[i].size() - pos_B - 1;
					const char *tmp_B = B[i].c_str();
					int val = -1;

					if(rev_B>=0 && pos_A >=0) {
						/* A[pos_A] + B[i][rev_B] + carry */
						a = ('?' == A[pos_A]) ? cur_d : (A[pos_A]-'0');
						val = a + (tmp_B[rev_B]-'0') + carry[pre_d][i];
					}
					else if(rev_B<0 && pos_A>=0) {
						/* A is longer than B[i]: A[pos_A] + carry */
						a = ('?' == A[pos_A]) ? cur_d : (A[pos_A]-'0');
						val = a + carry[pre_d][i];
					}
					else if(rev_B>=0 && pos_A <0) {
						/* B[i] is longer than A: B[i][rev_B] + carry */
						val = (tmp_B[rev_B]-'0') + carry[pre_d][i];
					}

					//TODO: how to store previous and current carry?
					carry[a][i] = (val > 9) ? true : false;

					// TODO: update digit count
					// (1) how to judge leading zero?
					// (2) how to judge the most significant carry, e.g. 958+42 = "1"000
					if(val != -1)
						current_digit_cnt[a][(val%10)]++;
					else
						continue;

					cout << "\nval = " << val << '\n';
					cout << "current_digit_cnt[" << a << "]" << "[" << (val%10) << "] = "
						 << current_digit_cnt[a][(val%10)] << '\n';

				} /* B[0] to B[n] */


				// TODO: Calculate the price
				current_price[a] = price(current_digit_cnt[a]);

				cout << "\npos_A = " << pos_A << ".....\n";
				cout << "a = " << a << "....\n"; 
				print_digit_cnt(current_digit_cnt, a);
				cout << "current_price = " << current_price[a] << "\n\n";
			
				// TODO: How to initialize the table?

				if(A[pos_A] != '?')	break;

			} /* previous '?': 0 to 9 */

		} /* current '?': 0 to 9 */

	} /* the least to most significant digit */


	/* Check for the last carry, e.g. 958+42 = "1"000 */
	for(int d=0; d<=9; ++d)
		for(int i=0; i<n; ++i)
			if(carry[d][i])
				current_digit_cnt[d][1]++;

//	for(int d=0; d<=9; ++d) {
//		cout << "d = " << d << " ..........\n";
//		print_digit_cnt(current_digit_cnt, d);
//	}

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

	cout << "\nMAX = " << max_cost(A, n) << '\n';

	return 0;
}
