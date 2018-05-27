#pragma once

#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;


class runtime_options {
private:
    std::vector<std::string> files;
    po::variables_map vm;
    po::options_description desc;

    runtime_options(po::options_description _desc, po::variables_map _vm, std::vector<std::string> _files) :
            desc(_desc),
            vm(_vm),
            files(_files) {
    }

public:
    static runtime_options parse(int argc, const char *argv[]) {
        std::vector<std::string> files;

        po::options_description desc("Allowed options");
        desc.add_options()
                ("help", "Print this documentation");


        po::options_description hidden;
        hidden.add_options()("files", po::value(&files), "files");

        po::options_description all_options;
        all_options.add(desc);
        all_options.add(hidden);


        po::positional_options_description p;
        p.add("files", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(all_options).positional(p).run(), vm);

        po::notify(vm);

        return runtime_options(desc, vm, files);
    }

    bool help_requested() {
        return vm.count("help") > 0;
    }

    bool has_files() {
        return files.size() > 0;
    }

    void print_help() {
        std::cout << desc << std::endl;
    }

    const std::vector<std::string> filenames() {
        return files;
    }
};

