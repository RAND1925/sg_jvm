
#include "Cmd.h"

#include "boost/program_options.hpp"
boost::program_options::options_description Cmd::dash_options("java-like");
boost::program_options::options_description Cmd::long_options("unix-like");
boost::program_options::options_description Cmd::hidden_options("*");
boost::program_options::options_description Cmd::options("all");
boost::program_options::positional_options_description Cmd::p;

Cmd Cmd::parse(int argc, TCHAR** argv) {

    Cmd cmd;
    namespace po = boost::program_options;
   
    po::variables_map vm;
    try {
        auto parsed = po::basic_command_line_parser(argc, argv)
            .options(options)
            .style(po::command_line_style::unix_style | po::command_line_style::allow_long_disguise)
            .positional(p)
            .allow_unregistered()
            .run();

        po::store(parsed, vm);

        po::notify(vm);

        cmd.helpFlag = vm.count("help");
        cmd.versionFlag = vm.count("version");

        return cmd;
    } catch (...) {
        return cmd;
    }

    
}

inline Cmd::Cmd() {
    namespace po = boost::program_options;

    dash_options.add_options()
        ("help,?", R"(get help)")
        ("version,v", R"(0.0.1)")
        ("Xre", "xre")
        ("cp", po::wvalue(&classpath), "classpath");
    options.add(dash_options);
    p.add("class", -1);
}
