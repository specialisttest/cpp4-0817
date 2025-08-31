#include <iostream>
#include <boost/dll.hpp>

int main(){
	// user32.dll MessageBoxA
	// dumpbin c:\windows\system32\user32.dll /EXPORTS
	system("chcp 1251 >nul");
	
	try {
		boost::dll::shared_library user32_lib("C:\\Windows\\System32\\user32.dll"); // 64-bit
		
		if (!user32_lib.is_loaded()) {
			std::cerr << "user32.dll NOT loaded" << std::endl;
			return 1;
		}
		
		if (!user32_lib.has("MessageBoxA")) {
			std::cerr << "MessageBoxA NOT found in user32.dll" << std::endl;
			return 2;
		}
		
		auto message_box = user32_lib.get<int(void*, const void*, const void*, int)>("MessageBoxA");
		
		std::cout << "MessageBoxA address: " << message_box << std::endl;
		
		int result = message_box (
			nullptr,
			"Hello from boost/dll!",
			"MessageBox example",
			0
		);
			
	}
	catch (const std::exception& e) {
		std::cerr << "Error:" << e.what() << std::endl;
	}
	
	return 0;
}
