#include <iostream>
#include <vector>
#include <algorithm>


void myAction(int k) {
	std::cout << k << " ";
}

int main(int argc, char** argv) {
	
	// value_type - тип значения, множество которых хранится в контейнере
	std::vector<int> nums = { 10, 20, 30, 40 , 50};
	
	std::for_each(nums.cbegin(), nums.cend(), myAction);
	std::cout << std::endl;
	
	std::for_each(nums.cbegin(), nums.cend(), 
		// функция
		[](int k){std::cout << k << " "; }
	);
	
	std::cout << std::endl;
	
	int count = 0;
	std::for_each(nums.cbegin(), nums.cend(), 
		// функтор
		[&count](int k){
			std::cout << k << " ";
			count++;
		}
	);
	std::cout << std::endl;

	std::for_each(nums.cbegin(), nums.cend(), 
		[](int k){std::cout << k << " "; }
	)(-1);
	
	std::cout << std::endl;

	
	std::cout << std::endl << "Count: " << count <<  std::endl;
	
	
	std::cout << "************" << std::endl;
	int divider = 4;
	for(auto& k : nums)
		if (k % divider == 0)
			std::cout << k << " ";
			
	std::cout << "\n************" << std::endl;
	
	std::for_each(nums.cbegin(), nums.cend(), 
		[divider](int k){
			if (k % divider == 0)
				std::cout << k << " ";
		}
	);
	
	std::cout << "\n************" << std::endl;
	
	//for(int k : nums)
	for(auto& k : nums)
		std::cout << ++k << " ";
		
	std::cout << std::endl;
	
	for(auto& k : nums)
		std::cout << k << " ";
		
	std::cout << std::endl;
	
	
}
