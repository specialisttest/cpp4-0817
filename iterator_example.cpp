#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <string>


int main() {
	
	// Пример итератора вектора
	std::vector<int> vec = { 10, 20, 30, 40 , 50};
	std::cout << "Vector elements (forward):  ";
	//std::random_access_iterator
	for ( auto it = vec.begin(); it != vec.end(); ++it) 
		std::cout << *it << " ";
		
	std::cout << std::endl;
	
	//[10, 20, 30]
	//  0   1   2
	//[0..3)
	
	std::cout << "Vector elements (backward): ";
	for ( auto it = vec.rbegin(); it != vec.rend(); ++it) 
		std::cout << *it << " ";
	std::cout << std::endl;		
	
	// Пример итератора списка
	std::list<std::string> lst = { "STL", "Boost", "C++"};
	std::cout << "List elements (forward):  ";
	//std::bidirectional_iterator
	for ( auto it = lst.begin(); it != lst.end(); ++it) 
		std::cout << *it << " ";
		
	std::cout << std::endl;	
}
