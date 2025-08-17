#include <iostream>
#include <vector>
#include <algorithm>

template<typename TInt>
class Rand {
public:
	
	Rand() : m_a(0), m_b(INT_MAX) {}
	Rand(TInt a, TInt b) : m_a(a), m_b(b) {	}
	
	TInt operator()() {
		return m_a + rand() % (m_b-m_a+1);
	}
private:
	TInt m_a;
	TInt m_b;
};


// Функтор
template<typename TInt, TInt a = 0, TInt b = INT_MAX>
class TRand {
public:
	TInt operator()() {
		return a + rand() % (b-a+1);
	}
};

// [1..100]
int rand_1_100() {
	return 1 + rand() % 100;
}


int main() {
	std::vector<int> v(10);
	//int i = 0;
	//std::generate(v.begin(), v.end(),
	//	[&i](){return i++; }
	//);
	
	//std::generate(v.begin(), v.end(), rand);
	//std::generate(v.begin(), v.end(), rand_1_100);
	//[4..20]
	//std::generate(v.begin(), v.end(), [](){ return 4 + rand()% (20-4+1);}); // since C++11
	//std::generate(v.begin(), v.end(), TRand<int,4,20>());
	std::generate(v.begin(), v.end(), Rand<int>(4,20));
	
	
	
	std::for_each(v.cbegin(), v.cend(),
		[](const auto k){ std::cout << k << " "; });
	
}
