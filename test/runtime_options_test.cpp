#include <boost/test/unit_test.hpp>

#include "runtime_options.h"

BOOST_AUTO_TEST_SUITE(jx_options)

    BOOST_AUTO_TEST_CASE(help_not_required_if_help_option_not_given) {
        const char *argv[] = {"jx"};
        auto options = runtime_options::parse(boost::size(argv), {});
        BOOST_CHECK(!options.help_requested());
    }

    BOOST_AUTO_TEST_CASE(help_required_if_help_option_given) {
        const char *argv[] = {"jx", "--help"};
        auto options = runtime_options::parse(boost::size(argv), argv);
        BOOST_CHECK(options.help_requested());
    }

    BOOST_AUTO_TEST_CASE(has_files_false_if_no_files_given) {
        const char *argv[] = {"jx"};
        auto options = runtime_options::parse(boost::size(argv), argv);
        BOOST_CHECK(!options.has_files());
    }

    BOOST_AUTO_TEST_CASE(has_files_true_if_files_given) {
        const char *argv[] = {"jx", "a"};
        auto options = runtime_options::parse(boost::size(argv), argv);
        BOOST_CHECK(options.has_files());
    }

    BOOST_AUTO_TEST_CASE(returns_supplied_filenames) {
        const char *argv[] = {"jx", "a"};
        auto options = runtime_options::parse(boost::size(argv), argv);
        BOOST_CHECK(options.has_files());
        BOOST_CHECK_EQUAL(std::string("a"), options.filenames()[0]);
    }

BOOST_AUTO_TEST_SUITE_END()