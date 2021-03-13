// sg_jvm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <iostream>
#include "Cmd.h"

int wmain(int argc, wchar_t**argv) {
    Cmd cmd = Cmd::parse(argc, argv);
    if (cmd.helpFlag) {
        std::wcout << "help" << std::endl; 
    } else if (cmd.versionFlag) {
        std::wcout << "version 0.0.1" << std::endl;
    } else {
        std::wcout << cmd.classpath << std::endl;
        //start jvm
    }
}
