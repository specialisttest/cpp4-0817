#include <iostream>
#include <vector>
#include <list>
#include <type_traits>
#include <string>
#include <algorithm>

template<typename T>
void print_container2(const T& c, int) {
    std::for_each(c.cbegin(), c.cend(),
	[](const auto& item){
		std::cout << "[" << item << "] ";
	});

    std::cout << "\n\n";
}

template<typename T>
void print_container2(const T& c, std::string) {
    std::for_each(c.cbegin(), c.cend(),
	[](const auto& item){
        std::cout << "\"" << item << "\" ";
	});
    std::cout << "\n\n";
}

template<typename T>
void print_container2(const T& c) {
	print_container2(c,  typename T::value_type());
}

template <typename T>
concept IntContainer = std::integral<typename T::value_type>;//std::same_as<typename T::value_type, int>;

template <typename T>
concept StringContainer = std::same_as<typename T::value_type, std::string>;

//template<typename T> requires std::integral<typename T::value_type>
template<IntContainer T> 
void print_container3(const T& c) {
    std::for_each(c.cbegin(), c.cend(),
	[](const auto& item){
		std::cout << "[" << item << "] ";
	});

    std::cout << "\n\n";
}

//template<typename T> requires std::same_as<typename T::value_type, std::string>
template<StringContainer T>
void print_container3(const T& c) {
    std::for_each(c.cbegin(), c.cend(),
	[](const auto& item){
		std::cout << "\"" << item << "\" ";
	});

    std::cout << "\n\n";
}

template<typename T>
void print_container4(const T& c) {
    using elem_type = typename T::value_type;//typedef typename T::value_type elem_type;
    
    std::for_each(c.cbegin(), c.cend(),
	[](const auto& item){
        if constexpr (std::is_integral_v<elem_type>) {
            std::cout << "[" << item << "] ";
        } else if constexpr (std::is_same_v<elem_type, std::string>) {
            std::cout << "\"" << item << "\" ";
        }
	});
	
    std::cout << "\n\n";
}

int main() {
    std::vector<int> ivec = {10, 20, 30, 40, 50};
    std::list<std::string> slist = {"Hello", "STL", "World"};
    
    std::cout << "************************" << std::endl;
	print_container2(ivec);
    print_container2(slist);
	std::cout << "************************" << std::endl;
    print_container3(ivec);
    print_container3(slist);
	std::cout << "************************" << std::endl;    
    print_container4(ivec);
    print_container4(slist);
    
    return 0;
}

