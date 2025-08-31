#include <iostream>
#include <boost/asio.hpp>

// gcc command line add: -lws2_32 -lwsock32
// linker line add :  C:\boost_1_88_0_my\boost_gcc\lib\*.a

using btcp = boost::asio::ip::tcp;

int main(int argc, const char* argv[]) {
	try {
		boost::asio::io_context ioctx;
		
		btcp::acceptor acceptor(ioctx, btcp::endpoint(btcp::v4(), 8080)); // 127.0.0.1::8080
		std::cout << "Server started on port 8080" << std::endl;
		while(true) {
			btcp::socket socket(ioctx);
			acceptor.accept(socket); // asio
	 		
			char buff[1024];
			boost::system::error_code ec;
			size_t len = socket.read_some(boost::asio::buffer(buff), ec); // async_read_some
			if (ec)
				std::cerr << ec << std::endl;
			else
				std::cout << std::string(buff, len) << std::endl;
		}
	} catch (...){
		std::cerr << "unknown error" << std::endl;
	}
	

}

