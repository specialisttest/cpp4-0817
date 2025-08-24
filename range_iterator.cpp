#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

template<typename T = int>// requires std::integral<T>
class Range{
private:
	T m_l = 0;
	T m_r = 0;

public:
	Range(T r) : m_r(r) {}
	Range(T l, T r) : m_l(l), m_r(r) {}
	
	class const_iterator // use since C++ 17
	{
		public:
			using iterator_category = std::input_iterator_tag;
			using value_type = decltype(m_l);
			using difference_type = decltype(m_l);
			using pointer = decltype(m_l)*;
			using reference = decltype(m_l)&;
			
	
	// depricated since C++17
	/*class const_iterator : public std::iterator<
		std::input_iterator_tag,
		decltype(m_l),
		decltype(m_l)>
	{
		public:
			using value_type = decltype(m_l);
			using reference = decltype(m_l)&;
	*/	
		private:
			value_type m_current;
			Range& m_owner;
			
		public:
			explicit const_iterator(Range& owner)
				: m_owner(owner), m_current(owner.m_l) {}
				
			explicit const_iterator(Range& owner, value_type current)
				: m_owner(owner), m_current(current) {}	
				
				
			// prefix increment
			const_iterator& operator++() {
				if (m_current < m_owner.m_r) m_current++;
				return *this;
			}
			
			// postfix increment
			const_iterator operator++(int) {
				const_iterator prev = *this;
				if (m_current < m_owner.m_r) m_current++;
				return prev;
			}
			
			bool operator == (const const_iterator& other) const {
				return m_current == other.m_current;
			}
			
			bool operator != (const const_iterator& other) const {
				return !(*this == other);
			}
			
			const reference operator *() {return m_current; }
			
	};
	
	const_iterator cbegin() {return const_iterator(*this); }
	const_iterator cend() {return const_iterator(*this, m_r); }

	const_iterator begin() {return const_iterator(*this); }
	const_iterator end() {return const_iterator(*this, m_r); }	
};

template<std::input_iterator It, typename TCh>
std::basic_ostream<TCh>& print(std::basic_ostream<TCh>& out, It it_start, It it_end) {
	for(auto it = it_start; it != it_end; ++it)
		out << *it << TCh(' ');
	return out;
}

template<typename TContainer, typename TCh>
std::basic_ostream<TCh>& print(std::basic_ostream<TCh>& out, const TContainer& cont) {
	return print(out, cont.cbegin(), cont.cend());
}

int main() {
	
	auto printLn = [](){ std::cout << "\n******************\n"; };
	
	//Range r1(2, 10); // 2 3 4 .. 9
	Range r(2,10); // 0  1  2 .. 9
	
	for(auto it = r.cbegin(); it != r.cend(); ++it)
		std::cout << *it << " ";
		
	printLn();
	
	for(const auto& el : r)
		std::cout << el << " ";

	printLn();		
	std::vector<int> v;
	std::transform(r.cbegin(), r.cend(), std::back_inserter(v), [](int k) {return k*k;});
	
	//for(auto k : v)
	//	std::cout << k << " ";
	
	//print(std::cout, v.cbegin(), v.cend()) << std::endl;	
	print(std::cout, v) << std::endl;
	
	return 0;
}
