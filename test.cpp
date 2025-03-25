#include <iostream>
#include "expression.hpp"

int main() {
    std::cout << "Running tests..." << std::endl;

    std::cout << "TestCopyTree()" << std::endl;
    std::cout << std::endl;
    TestCopyTree<double>();
    std::cout << std::endl;

    std::cout << "TestHelp_Expression_To_String()" << std::endl;
    std::cout << std::endl;
    TestHelp_Expression_To_String<double>();
    std::cout << std::endl;

    std::cout << "TestExpression_To_String()" << std::endl;
    std::cout << std::endl;
    TestExpression_To_String<double>();
    std::cout << std::endl;

    std::cout << "TestDiffiriention_help()" << std::endl;
    std::cout << std::endl;
    TestDiffiriention_help<double>();
    std::cout << std::endl;

    std::cout << "TestDiffiriention()" << std::endl;
    std::cout << std::endl;
    TestDiffiriention<double>();
    std::cout << std::endl;

    std::cout << "All tests completed." << std::endl;
    return 0;
}