#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>

#include <boost/program_options.hpp>

#include "runtime_options.h"
#include "pretty_printer.h"

int main(int argc, const char *argv[]) {
    std::cout << "jx - command line XML processor" << std::endl;

    auto options = runtime_options::parse(argc, argv);

    if (options.help_requested()) {
        options.print_help();
        return 0;
    }

    pretty_printer printer;
    
    pt::ptree tree;

    if (options.has_files()) {
        auto filenames = options.filenames();
        std::for_each(filenames.begin(), filenames.end(), [&](auto filename) -> void {
            pt::read_xml(filename, tree);
            printer.print(tree, 0);
        });
    } else {
        pt::read_xml(std::cin, tree);
        printer.print(tree, 0);
    }

    return 0;
}
