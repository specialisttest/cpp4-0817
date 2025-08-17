#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main(int argc, char** argv) {
	std::vector<int> v = { 10, 20, 30, 40, 50};
	std::copy(v.cbegin(), v.cend(),
		std::ostream_iterator<decltype(v)::value_type>(std::cout, " ") );
		
	std::cout << std::endl;

	std::copy_if(v.cbegin(), v.cend(),
		std::ostream_iterator<decltype(v)::value_type>(std::cout, " "),
		[](int k) { return k % 4 == 0; } );
		
	std::cout << std::endl;
	
	for(auto& k : v)
		if (k % 4 == 0)
			std::cout << k << " ";
	
	std::cout << std::endl;
	
	std::copy(++v.cbegin(), v.cend(),
		std::ostream_iterator<decltype(v)::value_type>(std::cout, " ") );
		
	std::cout << std::endl;
	
	std::copy(v.crbegin(), v.crend(),
		std::ostream_iterator<decltype(v)::value_type>(std::cout, " ") );
	
}
