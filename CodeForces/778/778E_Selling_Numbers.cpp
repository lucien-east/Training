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

long long max_cost(const string &A, const unsigned int &n)
{
	long long tmp_cost;
	long long max = 0;
	long long current_price[10];
	

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

	cout << max_cost(A, n) << '\n';

	return 0;
}
