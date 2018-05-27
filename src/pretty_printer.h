#pragma once

#include <boost/property_tree/ptree.hpp>
#include "color_palette.h"

namespace pt = boost::property_tree;

class pretty_printer {
public:

    std::string indent(int level) {
        std::string s;
        for (int i = 0; i < level; i++)
            s += "  ";
        return s;
    }


    std::string colorize_attribute(const std::string &key, const std::string &value) {
        return " "
               + color_palette::attribute
               + key
               + color_palette::punct
               + "=\""
               + color_palette::text
               + value
               + color_palette::punct
               + "\"";
    }

    auto colorize_text(const std::string text) {
        return color_palette::text + text;
    }

    bool is_attribute(const std::string &name) {
        return name == std::string("<xmlattr>");
    }

    void print_attributes(pt::ptree &pt) {
        for (pt::ptree::iterator pos = pt.begin(); pos != pt.end(); ++pos) {
            if (is_attribute(pos->first)) {
                auto attr = pos->second.begin();
                std::cout << colorize_attribute(attr->first, attr->second.data());
            }
        }
    }

    void print(pt::ptree &pt, int level) {
        if (pt.empty()) {
            std::cout << colorize_text(pt.data());
        } else {
            for (pt::ptree::iterator pos = pt.begin(); pos != pt.end();) {
                if (!is_attribute(pos->first)) {
                    std::cout << indent(level)
                              << color_palette::punct
                              << "<"
                              << color_palette::element
                              << pos->first;
                    print_attributes(pos->second);
                    std::cout << color_palette::punct
                              << ">";

                    if (!pos->second.empty())
                        std::cout << std::endl;

                    print(pos->second, level + 1);

                    if (!pos->second.empty())
                        std::cout << indent(level);

                    std::cout << color_palette::punct
                              << "</"
                              << color_palette::element
                              << pos->first
                              << color_palette::punct
                              << ">";
                    std::cout << std::endl;
                }
                ++pos;
            }
        }
    }


};
