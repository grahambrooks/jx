#include <boost/test/unit_test.hpp>
#include <iostream>

#include "pretty_printer.h"

BOOST_AUTO_TEST_SUITE(pretty_printing)

    BOOST_AUTO_TEST_CASE(prints_attributes_in_attribute_colour) {
        pretty_printer printer;

        std::cout << printer.print_attribute("k", "v");
        BOOST_CHECK_EQUAL(printer.print_attribute("k", "v"), " k=\"v\"");

    }


BOOST_AUTO_TEST_SUITE_END()