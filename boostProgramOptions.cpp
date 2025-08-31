#include <iostream>
#include <boost/program_options.hpp>

// gcc compiler options: -I
// link options -L library_folder

// Building boost using msvc
// 1. Download and extract boost lib
// 2. Make toolchain available in command line (using PATH) (skip for msvc)
// 3. .\bootstrap msvc or .\bootstrap
// 4. .\b2 --prefix=boost_msvc install

// Building boost using gcc
// 1. Download and extract boost lib
// 2. Make toolchain available in command line (using PATH)
// 3. .\bootstrap gcc
// 4. .\b2 --prefix=boost_gcc install

// boostProgramOptions.exe --verbosity 3
namespace bpo = boost::program_options;

int main(int argc, const char* argv[])
{
    boost::program_options::options_description dest("My test utility usage boostProgramOptions.exe [options]");
    dest.add_options()
        ("help,h", "Show help") // --help -h
        ("verbosity,v", bpo::value<int>()->default_value(1), "Verbosity level 0-5");

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, dest), vm);

    bpo::notify(vm);
    dest.print(std::cout);

    if (vm.count("verbosity")) {
        int verb = vm["verbosity"].as<int>();
        std::cout << "verbosity level: " << verb << std::endl;
    }


}

