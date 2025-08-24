#include <iostream>
#include <memory>
#include <cstring>
#include <vector>
#include <algorithm>
#include <chrono>

template<typename T>
class LogAllocator {
public:
	using value_type = T; // typedef T value_type
	LogAllocator() = default;
	
	template<typename U> LogAllocator(const LogAllocator<U>&) {}

	T* allocate( std::size_t n ) {
		std::cout  << "Allocating " << n << " elements" << std::endl;
		return static_cast<T*>(::operator new (n * sizeof(T)));
	}
	
	void deallocate( T* p, std::size_t n ){
		std::cout  << "Deallocating " << n << " elements" << std::endl;
		::operator delete(p);
	}
};

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

template<typename T>
void print(T it_start, T it_end) {
	for (auto it = it_start; it != it_end; ++it)
		std::cout << (int) *it << " ";
	std::cout <<std::endl;
}

template<typename T>
class my_allocator {

public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;	
	
private:
	void* m_mem;		// my "heap" start
	size_t m_size;		// size of my "heap"
	void* m_cursor;		// pointer next free block
	size_t m_maxElCount;// maximum elements
	size_t m_elSize;	// memory size for one element
	
public:
	
	my_allocator() = delete;
	
	my_allocator(void* mem, size_t size) :
		m_mem(mem),
		m_size(size),
		m_cursor(mem),
		m_maxElCount(size / sizeof(T)),
		m_elSize(sizeof(T)) {}
		
	size_t max_size() const noexcept {
		return m_maxElCount;
	}
	
	constexpr pointer allocate(size_t n) {
		//std::cout << __FUNCTION__ << " " << n << " elements requested" << std::endl;
		if (!m_mem) throw std::bad_alloc();
		if ( n > m_maxElCount - (static_cast<pointer>(m_cursor)-static_cast<pointer>(m_mem)) ) 
			throw std::bad_alloc();
		
		pointer ptr = (pointer) m_cursor;
		m_cursor = ptr + n;
		return ptr;
	}
	
	void deallocate(pointer p, std::size_t n) {
		//std::cout << __FUNCTION__ << " " << n << " elements deallocated" << std::endl;
	}
	
	template<class U, class... Args>
	void construct(U* p, Args&&... args) {
		::new ((void*)p) U(std::forward<Args>(args)...); // Non-allocating 
	}
	
	template<class U>
	void destroy(U* p) {
		p->~T();
	}
};

int main(int argc, char** argv) {
	Coords c; // stack
	
	Coords* pCoord = new Coords; // heap
	Coords* aCoords = new Coords[2]; // heap
	
	//std::unique_ptr<Coords> uCoords = std::make_unique<Coords>(1,1); //heap
	std::unique_ptr<Coords> uCoords(new Coords(1,1)); // heap
	std::cout << uCoords->x() << ", " << uCoords->y() << " id: " << uCoords->id()<< std::endl;
	
	std::shared_ptr<Coords[]> listCoords {std::make_shared<Coords[]>(3)}; //heap
	listCoords.reset();
	
	delete pCoord; // heap
	delete[] aCoords;
	
	constexpr int buffSize = 64;
	char buff[buffSize]; // stack
	std::generate(buff, buff + buffSize, [](){return 0;});
	print(buff, buff + buffSize);
	
	// Non-allocating new
	Coords* coordsInStack = new (buff) Coords[3]; // object in buff (stack)
	print(buff, buff + buffSize);
	coordsInStack->~Coords();
	print(buff, buff + buffSize);
	//delete coordsInStack; // do not use - crash (due to buff on stack)
	
	//std::unique_ptr<Coords> bCoords(new(buff) Coords(1,1)); // do not use - crash (due to buff on stack)
	//std::cout << bCoords->x() << ", " << bCoords->y() << " id: " << bCoords->id()<< std::endl;
	
	std::vector<int, LogAllocator<int>> vec;
	vec.push_back(42);
	vec.push_back(24);
	{
		constexpr size_t memSize = 1024;
		//char mem[memSize];
		char* mem = new char[memSize];
		memset(mem, 0, memSize);
		
		
		my_allocator<int> alloc(mem, memSize);
		std::vector<int, decltype(alloc)> mvec(alloc);
		
		mvec.reserve(10);
		for(int i=0; i < 10; i++)
			mvec.push_back(i);
			
		print(mem, mem + memSize);
		
		print(mvec.cbegin(), mvec.cend());
		
		delete[] mem;
		
	}
	{
		constexpr size_t memSize = 1024 * 1024 * 8;
		//char mem[memSize];
		char* mem = new char[memSize];
		memset(mem, 0, memSize);
		
		my_allocator<int> alloc(mem, memSize);
		std::vector<int, decltype(alloc)> mvec(alloc);
		std::vector<int> svec; // std::allocator
		
		const size_t allocElementCount = 100000;
		//mvec.reserve(allocElementCount);
		//svec.reserve(allocElementCount);
		
		auto t1_start = std::chrono::high_resolution_clock::now();

		for(int i=0; i < allocElementCount; i++)
			mvec.push_back(i);
			
		auto t1_stop = std::chrono::high_resolution_clock::now();
		auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(t1_stop - t1_start);
		std::cout << "Time taken (my_allocator): " << duration1.count() << " microseconds" << std::endl;		

		delete[] mem;
		
		auto t2_start = std::chrono::high_resolution_clock::now();

		for(int i=0; i < allocElementCount; i++)
			svec.push_back(i);
			
		auto t2_stop = std::chrono::high_resolution_clock::now();
		auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(t2_stop - t2_start);
		std::cout << "Time taken (std::allocator): " << duration2.count() << " microseconds" << std::endl;
	}
	
	
	
	
}
