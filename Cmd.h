#pragma once 

#include <string>
#include <vector>

#include "boost/program_options.hpp"

struct Cmd {
	bool helpFlag = false;
	bool versionFlag = false;

    std::wstring classpath;
    std::wstring jrePath;
    std::vector<std::wstring> args;

    const static option long_options[];


    static Cmd parse(int argc, wchar_t** argv);
};

