cmake_minimum_required(VERSION 3.10)
project(jx)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/main.cpp src/pretty_printer.h src/color_palette.h src/color_palette.cpp)

set(TEST_FILES
        test/test_main.cpp
        test/runtime_options_test.cpp test/pretty_printer_test.cpp src/color_palette.cpp)
add_executable(jx ${SOURCE_FILES})

add_executable(jx_test ${TEST_FILES})

include_directories(src)

find_package(Boost 1.67.0 REQUIRED COMPONENTS system program_options)
include_directories(${Boost_INCLUDE_DIR})

# target_compile_definitions(jx_test PRIVATE "BOOST_DYN_LINK=1")



target_link_libraries(jx ${Boost_LIBRARIES})

target_link_libraries(jx_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(jx_test ${Boost_LIBRARIES})

target_include_directories(jx_test PRIVATE ${Boost_INCLUDE_DIR})

target_compile_definitions(jx_test PRIVATE "BOOST_TEST_DYN_LINK=1")
