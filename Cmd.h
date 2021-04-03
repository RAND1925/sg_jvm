#pragma once 

#include <string>
#include <vector>

#include "util.h"

#include "boost/program_options.hpp"

struct Cmd {

	bool helpFlag = false;
	bool versionFlag = false;
    std::wstring classpathOption;
    std::wstring XjreOption;
    std::wstring classOption;
    std::vector<std::wstring> args;
  

    static boost::program_options::options_description dash_options;
    static boost::program_options::options_description long_options;
    static boost::program_options::options_description hidden_options;
    static boost::program_options::options_description options;
    static boost::program_options::positional_options_description p;

    static Cmd parse(int argc, TCHAR** argv);

private:
    Cmd();
};

