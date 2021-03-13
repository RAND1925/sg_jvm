#include "Cmd.h"

const option Cmd::long_options[]{
      { L"help", no_argument, nullptr, '?'},
      { L"version", no_argument, nullptr, 'v'},
      { L"cp", required_argument, nullptr, 'c'},
      { L"classpath", required_argument, nullptr, 'c'},
      { L"jar", required_argument, nullptr, 'j'},
      { L"Xjre", required_argument, nullptr, 'j'},
      {0, 0, 0, 0}
};

Cmd Cmd::parse(int argc, wchar_t** argv) {

    int option_index = 0;
    int c = 0;
    Cmd cmd;
    while (true) {

        c = getopt_long_only(argc, argv, L"?", long_options, &option_index);
        switch (c) {
        case -1:
            return cmd;
        case 'v':
            cmd.versionFlag = true;
            break;
        case ':':
        case '?':
            cmd.helpFlag = true;
            break;
        case 'c':
            cmd.classpath = optarg;
            break;;
        case 'j':
            cmd.XjreOption = optarg;
        }
    }
}
