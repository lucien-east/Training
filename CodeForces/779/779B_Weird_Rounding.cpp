#include <iostream>
#include <string>

int num_of_digit_to_erase(const std::string &num, const int target_k)
{
	int ans = 0;
	int len = num.length();
	
	std::cout << "len=" << len << ", " << num.at(0) << std::endl;
	std::cout << "---" << *(num.rbegin()) << "---";

	for(auto rit=num.rbegin(); rit!=num.rend(); ++rit)
	{
		// TODO: greedy	
	}	

	std::cout << std::endl;

	return ans;
}

int main()
{
	std::string input_num;
	int target_k;
	int ans;

	std::cin >> input_num >> target_k;

	ans = num_of_digit_to_erase(input_num, target_k);
	std::cout << ans << std::endl;
	
	return 0;
}
