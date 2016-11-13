#include <iostream>
#include <limits>
#include <algorithm>
#include <ios>
#define endl ('\n')

int main()
{
	std::ios_base::sync_with_stdio(false);
	// b=x[0], d=x[1], s=x[2]
	long long x[3];
	long long missed_meals;

        std::cin >> x[0] >> x[1] >> x[2];
	std::sort(x, x+3);
	missed_meals = 2*(x[2]-1)-x[1]-x[0];
	missed_meals = (x[1]!=x[2])?missed_meals:(std::max(0ll, x[2]-x[0]-1));
	std::cout << missed_meals << endl;

	return 0;
}
