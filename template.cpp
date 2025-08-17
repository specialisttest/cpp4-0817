#include <iostream>

//using std::endl;
//using std::cout;
//using namespace std;

namespace my {
	
	/*int min(int a, int b) {
		return (a < b) ? a : b;
	}
	
	long min(long a, long b) {
		return (a < b) ? a : b;
	}

	double min(double a, double b) {
		return (a < b) ? a : b;
	}*/
	
	template<typename T>
	T min(T a, T b) {
		return (a < b) ? a : b;
	}

	template<typename T, T b =0 /*since C++20*/ >
	bool is_greater(T a) {
		return a > b;
	}


}

int main() {
	std::cout << "Hello" << std::endl;
	//cout << "Hello" << endl;
	std::cout << my::min<int>(3, 1) << std::endl;
	std::cout << my::min(3L, 1L) << std::endl;		// min<long>
	std::cout << my::min(2.5, 1.5) << std::endl;	// min<double>
	
	std::cout << std::boolalpha << my::is_greater<int, 5>(7) << std::endl;
	std::cout << std::boolalpha << my::is_greater<double, 1.5>(0.5) << std::endl;
	std::cout << std::boolalpha << my::is_greater<int>(2) << std::endl;
	
}
