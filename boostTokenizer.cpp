#include <iostream>
#include <string>

#include "boost/tokenizer.hpp"

int main(int argc, const char* argv[]) {
	std::string text = "This is, a sample sentence!";
	boost::tokenizer<> tok(text);
	for(boost::tokenizer<>::iterator it = tok.begin(); it != tok.end(); ++it)
		std::cout << *it << std::endl;
	
	return 0;
}
