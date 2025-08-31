#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//#define USE_BOOST
//#ifdef USE_BOOST

#if __cplusplus < 201703L
	#include <boost/filesystem.hpp>
	namespace fs = boost::filesystem;
	//#warning Using boost
#else
	#include <filesystem>
	namespace fs = std::filesystem;
	//#warning Using std
#endif



int main(int argc, const char* argv[]){
	try {
		fs::path directoryPath = "."; //__FILE_NAME__;
		
		if (!fs::exists(directoryPath))
			throw std::string("not exists");
		
		if (!fs::is_directory(directoryPath))
			throw std::string("not a directory");
			
		for(const auto& entry : fs::directory_iterator(directoryPath)) {
			if(entry.is_directory()) std::cout << "[directory]";
			if(entry.is_regular_file()) std::cout << "[file]";
			if(entry.is_symlink()) std::cout << "[link]";
			std::cout << " " << entry.path() << std::endl;
		}
		
		std::vector<std::string> dirs;
		for(const auto& entry : fs::directory_iterator(directoryPath))
			dirs.push_back(entry.path().string());
			
		std::sort(dirs.begin(), dirs.end());
		std::cout << " ============= Sorted ===============" << std::endl;
		for(auto& name : dirs)
			std::cout << name << std::endl;
		
		
	}
	catch(const std::string& err) {
		std::cerr << "Error: " << err << std::endl;
	}
}
