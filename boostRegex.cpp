#include <iostream>
#include <vector>
#include <string>

#include "boost/regex.hpp"

// regx101.com
// \+(\d{1,4})-([1-9]\d{2})-(\d{3})-(\d{2})-(\d{2})

int main(int argc, const char* argv[]) {
	std::vector<std::string> phoneNumbers = {"+7-903-123-45-67", "+7-abc-123-45-67", "+7-003-123-45-67"};
	boost::regex pnRegex("^\\+(\\d{1,4})-([1-9]\\d{2})-(\\d{3})-(\\d{2})-(\\d{2})$");
	boost::smatch matchResult;
	
	for(const auto& pn : phoneNumbers) {
		if (boost::regex_match(pn, matchResult, pnRegex)) {
			std::cout << pn << " is correct phone" << std::endl;
			for(const auto& group : matchResult)
				std::cout << '\t' << group << std::endl;
		}
		else
			std::cout << pn << " is NOT a phone" << std::endl;
	}
	
	std::string text = "1, 023, 17, 29, 18, 89, , 105, 24, 56";
	boost::regex re("\\d+");
	
	auto bi = boost::sregex_iterator(text.cbegin(), text.cend(), re);
	auto ei = boost::sregex_iterator();
	for(auto i = bi; i != ei; ++i)
		std::cout << *i  <<std::endl;
	
	
	return 0;
}
