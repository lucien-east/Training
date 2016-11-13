#include <iostream>
#include <limits>
#include <algorithm>
#include <ios>
#define endl ('\n')

int main()
{
	std::ios_base::sync_with_stdio(false);
	long long b, d, s, days;

        std::cin >> b >> d >> s;

	days = std::max(b, std::max(d, s))-1;
	std::cout << std::max(days-b, 0ll)+std::max(days-d, 0ll)+std::max(days-s, 0ll) << endl;

	return 0;
}
