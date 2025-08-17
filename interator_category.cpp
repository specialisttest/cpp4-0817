#include <iostream>
#include <vector>
#include <list>
#include <algorithm>


namespace my
{
	// since C++20 (use concept)
	template<std::bidirectional_iterator BDIt>
	void alg(BDIt it_start, BDIt it_end ) {
		std::cout <<"modern implementation alg with bidirectional_iterator" << std::endl;
	}
	
	template<std::random_access_iterator RAIt>
	void alg(RAIt it_start, RAIt it_end) {
		std::cout <<"modern implementation alg with random_access_iterator" << std::endl;
	}
	
	
	
	// work with C++03
	namespace legacy {
		
		template<typename BDIt>
		void alg(BDIt it_start, BDIt it_end, std::bidirectional_iterator_tag) {
			std::cout <<"legacy implementation alg with bidirectional_iterator" << std::endl;
		}
		
		template<typename RAIt>
		void alg(RAIt it_start, RAIt it_end, std::random_access_iterator_tag) {
			std::cout <<"legacy implementation alg with random_access_iterator" << std::endl;
		}
		
		template<class It>
		void alg(It it_start, It it_end) {
			alg(it_start, it_end, typename std::iterator_traits<It>::iterator_category());
		}
		
	}
}
int main() {
	
	std::vector<int> v(10); // std::random_access_iterator
	std::list<int>   l(10); // std::bidirectional_iterator

	my::legacy::alg(v.begin(), v.end());
	my::legacy::alg(l.begin(), l.end());
	
	my::alg(v.begin(), v.end());
	my::alg(l.begin(), l.end());
	
}
