# jx

[jq](https://stedolan.github.io/jq/) for XML

Having spent sime time working in clojure jx is a chance to exercise some C++ skills as well as being potentially useful on projects invovling XML.

## Dependencies

    brew install cmake boost

## Building

run

    cmake .

from the project folder to generate the jx executable in cmake-build-debug

Testing with example xml

    cmake-build-debug/jx test-data/books.xml

