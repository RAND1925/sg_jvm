// sg_jvm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include "windows.h"
#include "Cmd.h"
#include "Classpath.h"
#include "ClassFile.h"

int wmain(int argc, TCHAR** argv) {
    Cmd cmd = Cmd::parse(argc, argv);

    if (cmd.helpFlag) {
        std::cout << cmd.dash_options << std::endl; 
    } else if (cmd.versionFlag) {
        std::cout << "version 0.0.1" << std::endl;
    } else {
        std::cout << "ok";
        // start jvm
        Classpath cp{cmd};
        auto absolute_path= cp.get_absolute_path(L"Object");
        
        ClassFile class_file;
        class_file.read(absolute_path);
    }
    
    return 0;
}
