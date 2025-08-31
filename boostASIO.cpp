#include <iostream>
#include <vector>

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

// gcc command line add: -lws2_32 -lwsock32
// linker line add :  C:\boost_1_88_0_my\boost_gcc\lib\*.a or C:\boost_1_88_0_my\boost_gcc\lib\*-mgw14-mt-x64-1_88.a

void simple_timer() {
	boost::asio::io_context ioctx;
	boost::asio::steady_timer timer(ioctx, boost::asio::chrono::seconds(1));
	std::cout << "simple wait started" << std::endl;
	timer.wait(); // std::this_thread::sleep(1);
	std::cout << "simple timer timeout" << std::endl;	
}

void timer_thread() {
	boost::asio::io_context ioctx;
	boost::asio::steady_timer timer(ioctx, boost::asio::chrono::seconds(1));
	std::cout << "thread wait started" << std::endl;
	
	timer.async_wait([](const boost::system::error_code& ec){
		std::cout << "timer timeout thread id: " << boost::this_thread::get_id() << std::endl;
	});
	
	std::cout << "this thread id: " << boost::this_thread::get_id() << std::endl;
	ioctx.run();
	std::cout << "ioctx event loop exited" << std::endl;	
}

void another_thread() {
	boost::asio::io_context ioctx;
	boost::asio::steady_timer timer(ioctx, boost::asio::chrono::seconds(1));
	std::cout << "another thread wait started" << std::endl;
	
	timer.async_wait([](const boost::system::error_code& ec){
		std::cout << "timer timeout thread id: " << boost::this_thread::get_id() << std::endl;
	});
	
	std::cout << "this thread id: " << boost::this_thread::get_id() << std::endl;
	
	auto t = boost::thread([&ioctx](){
		std::cout << "ioctx event loop thread id: " << boost::this_thread::get_id() << std::endl;
		ioctx.run();
		std::cout << "ioctx event loop exited" << std::endl;	
	});
	
	t.join();
}

void multi_timer() {
	boost::asio::io_context ioctx;
	std::cout << "multi timer wait started" << std::endl;
	
	std::vector<std::unique_ptr<boost::asio::steady_timer>> timers(3);
	
	for(int i = 0; i < timers.size(); i++){
		timers[i].reset(new boost::asio::steady_timer(ioctx, boost::asio::chrono::seconds(1)));
		std::cout << i << " timer wait started" << std::endl;
		timers[i]->async_wait([i](const boost::system::error_code& ec){
			std::cout << i << " timer timeout thread id: " << boost::this_thread::get_id() << std::endl;
		});
	}
	
	std::cout << "this thread id: " << boost::this_thread::get_id() << std::endl;
	
	auto t = boost::thread([&ioctx](){
		std::cout << "ioctx event loop thread id: " << boost::this_thread::get_id() << std::endl;
		ioctx.run();
		std::cout << "ioctx event loop exited" << std::endl;	
	});
	
	t.join();
}

int main(int argc, const char* argv[]) {
	simple_timer();
	timer_thread();
	another_thread();
	multi_timer();
}

