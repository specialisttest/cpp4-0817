#include <iostream>
#include <string>
#include <boost/variant.hpp>

class Coords {
private:
	int m_x = 0;
	int m_y = 0;
	int m_id;
	
	static int last_id;
public:
	Coords(int x = 0, int y = 0) : m_x(x), m_y(y) {
		m_id = ++Coords::last_id;
		std::cout << "Coords created. id:" << m_id << std::endl;
	}
	
	int x() const {return m_x;}
	int y() const {return m_y;}
	int id() const {return m_id;}
		
	~Coords () {
		std::cout << "Coords deleted. id: " << m_id << std::endl;
	}
};
int Coords::last_id = 0;

int main() {
	// Equivalent of C union
	typedef boost::variant<int, float, double> NumericDataType;
	
	 NumericDataType myType = 3.142d;
	 std::cout << myType << std::endl;
	 myType = 1.98f;
	 std::cout << myType << std::endl;
	 myType = static_cast<double>(3.14);
	 std::cout << myType << std::endl;
	 myType = 123;
	 std::cout << myType << std::endl;
	 
	 // compile error
	 // myType = std::string("abc");
	 
	 boost::variant<long, std::string, Coords> myVariant;
	 boost::variant<long, std::string, Coords> myVariant2(myVariant);
	 
	 Coords c(1,2);
	 boost::variant<long, std::string, Coords> myVariant3(c);
	 
	 myVariant = 24L;
	 myVariant = std::string("abc");
	 myVariant = Coords(3,4);
	 
	 try {
		 Coords c2 = boost::get<Coords>(myVariant);
		 //std::string s2 = boost::get<std::string>(myVariant);  // exception, wrong type
		 std::cout << c2.x() << ", " << c2.y() << " id: " << c2.id()<< std::endl;
	 }
	 catch(boost::bad_get& err) {
	 	std::cerr << "Error: " << err.what() << std::endl;
	 }
	 
}

