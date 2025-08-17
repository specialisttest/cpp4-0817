#include <iostream>
#include <type_traits>
#include <concepts>

template<typename T>
void process(const T& val) {
	// constexpr - вычисление (по возможности) выражени€ на этапе компил€ции (since C++20)
	if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T> /*since C++11*/)
		std::cout << "Value: " << val << std::endl;
	else
		std::cout << "Unsupported type" << std::endl;
}

template<typename T>
concept enable_num_types = std::same_as<T, int>  || std::same_as<T, double>; // since C++20

template<enable_num_types T>
void print(const T& val) {
	std::cout << "Print Value: " << val << std::endl;
}

int main(){
	process(42); 		// int
	process(3.14d);  	// double
	process("text"); 	// Unsupported type
	
	print(42); 		// int
	print(3.14d);  	// double
	//print("text"); 	// compile error
	
	
	return 0;
}

