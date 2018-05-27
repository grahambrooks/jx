#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>

#include <boost/program_options.hpp>

#include "runtime_options.h"

#define ESC "\033"
#define COL(c) (ESC "[" c "m")
#define COLRESET (ESC "[0m")

static const char* colors[] =
        {COL("1;30"),
         COL("0;39"),
         COL("0;39"),
         COL("0;39"),
         COL("0;32"),
         COL("1;39"),
         COL("1;39")};

#define FIELD_COLOR COL("34;1")

namespace pt = boost::property_tree;


std::string indent(int level) {
    std::string s;
    for (int i = 0; i < level; i++)
        s += "  ";
    return s;
}



std::string element_color(const std::string& text) {
  return COL("1;30") + text + COLRESET;
}


void print_attribute(pt::ptree& pt) {
  pt::ptree::iterator pos = pt.begin();
  std::cout << "\"";
  std::cout << colors[1];
  std::cout  << pos->first;
  std::cout << COLRESET;
  std::cout  << "\"=\"";
  std::cout  << FIELD_COLOR;
  std::cout  << pos->second.data();
  std::cout << COLRESET;
  std::cout  << "\"";
  std::cout  << std::endl;
}

void printTree(pt::ptree &pt, int level) {
  if (pt.empty()) {
    std::cout << "\"" << colors[4] << pt.data() << COLRESET << "\"";
  } else {
    if (level) std::cout << std::endl;

    std::cout << indent(level) << "{" << std::endl;
    
    for (pt::ptree::iterator pos = pt.begin(); pos != pt.end();) {
      if (pos->first == std::string("<xmlattr>")) {
        print_attribute(pos->second);
      }
      else {
        std::cout << indent(level + 1) << "\"" << element_color(pos->first) << "\": ";
        
        printTree(pos->second, level + 1);
      }
      ++pos;
      if (pos != pt.end()) {
        std::cout << ",";
      }
      std::cout << std::endl;
    }
    
    std::cout << indent(level) << "}" << std::endl;
  }
}



int main(int argc, const char * argv[]) {
  std::cout << "jx - command line XML processor" << std::endl;
  
  auto options = runtime_options::parse(argc, argv);
  
  if (options.help_requested()) {
    options.print_help();
    return 0;
  }
  
  pt::ptree tree;
  
  if (options.has_files()) {
    auto filenames = options.filenames();
        std::for_each(filenames.begin(), filenames.end(), [&](auto filename) -> void {pt::read_xml(filename, tree);
            printTree(tree, 0);
            std::cout << "done" << std::endl;});
  } else {
    pt::read_xml(std::cin, tree);
    printTree(tree, 0);
    
    std::cout << "done" << std::endl;}
  
  return 0;
}
