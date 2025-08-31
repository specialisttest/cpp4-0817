#include <iostream>
#include <string>

#include <stack>
#include <vector>


bool verify_brackets(const std::string& inp) {
	/*std::vector<char> v;
	v.reserve(inp.size());
	std::stack<char, decltype(v)> st(v);*/
	
	std::stack<char> st; // deque
	
	for(auto it = inp.cbegin(); it != inp.cend(); ++it ) {
		char ch = *it;
		if (ch == '(' || ch == '[')
			st.push(ch);
		else
			if (ch == ')' || ch == ']')
				if (st.empty()) return false;
				else {
					char ch_open = st.top();
					st.pop();
					if ( (ch == ')' && ch_open !='(') || (ch == ']' && ch_open !='['))
						return false;
				}
	
	}
	
	return st.empty();
}

int main() {
	std::string input = "abc (  cde )  ( [ ( ] ) ) abc () 22";
	std::cout << input << std::endl;
	std::cout << std::boolalpha << verify_brackets(input) <<std::endl;
	
}
