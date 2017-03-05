#include <iostream>
#include <string>
#include <cstdlib>

unsigned int num_of_digit_to_erase(const std::string &num, const unsigned int target_k)
{
	unsigned int ans = 0;
	unsigned int num_zero = 0;
	const size_t len = num.length();
	char digit;
	
	if(len <= target_k) {
		// It is guaranteed that answer exists
		return (len-1);
	}

	for(std::string::const_reverse_iterator rit=num.rbegin(); rit!=num.rend(); ++rit) {
		if (num_zero == target_k) {
			break;
		}

		digit = *rit;
		if (0 == atoi(&digit)) {
			++num_zero;
			continue;
		}

		++ans;
	}	

	// It is guaranteed that answer exits
	return (num_zero==target_k) ? ans : (len-1);
}

int main()
{
	std::string input_num;
	unsigned int target_k;
	unsigned int ans;

	std::cin >> input_num >> target_k;

	ans = num_of_digit_to_erase(input_num, target_k);
	std::cout << ans << std::endl;
	
	return 0;
}
