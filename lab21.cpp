#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

template<typename T>
void print_container(const T& c) {
	std::for_each(c.cbegin(), c.cend(),
		[](const auto& item){
			std::cout << item << " ";
		}
	);
	
	std::cout <<std::endl;
}

template<typename T> requires std::integral<typename T::value_type>
void fill_random( T& c) {
	srand(2025);
	//srand(std::time({}));
	std::generate(c.begin(), c.end(), /*rand*/ [](){ return 1+rand()%100;});
}


int main() {
	std::vector<int> source(10000000);
	std::vector<int> result(3);
	
	fill_random(source);
	//print_container(source);
	
	// Sort and copy O(n*log (n))
	std::cout << "Sort and copy algorithm" << std::endl;
	auto t1_start = std::chrono::high_resolution_clock::now();
	
	std::sort(source.begin(), source.end());
	std::copy(source.cbegin(), source.cbegin()+result.size(), result.begin());
	
	auto t1_stop = std::chrono::high_resolution_clock::now();
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(t1_stop - t1_start);
	
	std::cout << "Time taken (sort and copy): " << duration1.count() << " microseconds" << std::endl;
	print_container(result);
	
	// Custom search ( O(n) )
	fill_random(source);
	
	std::cout << "Custom algorithm (copy min)" << std::endl;
	
	auto t2_start = std::chrono::high_resolution_clock::now();

	std::fill(result.begin(), result.end(), INT_MAX);
	int max_in_min = INT_MAX;
	std::for_each(source.cbegin(), source.cend(), [&max_in_min, &result](int k) {
		if (k < max_in_min) {
			*std::find(result.begin(), result.end(), max_in_min) = k;
			max_in_min = *std::max_element(result.cbegin(), result.cend());
		}
	});
	//std::sort(result.begin(), result.end());
	auto t2_stop = std::chrono::high_resolution_clock::now();
	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(t2_stop - t2_start);
	
	std::cout << "Time taken (sort and copy): " << duration2.count() << " microseconds" << std::endl;
	print_container(result);
	
	// partial sort and copy O(n*log (k)) ==  O(n) k = 3
	std::cout << "Partial sort and copy algorithm" << std::endl;
	auto t3_start = std::chrono::high_resolution_clock::now();
	
	std::partial_sort(source.begin(), source.begin() + result.size(), source.end());
	std::copy(source.cbegin(), source.cbegin()+result.size(), result.begin());
	
	auto t3_stop = std::chrono::high_resolution_clock::now();
	auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(t3_stop - t3_start);
	
	std::cout << "Time taken (sort and copy): " << duration3.count() << " microseconds" << std::endl;
	print_container(result);
	
	// test with -O3 optimization
	
}
