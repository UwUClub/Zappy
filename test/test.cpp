#include <iostream>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("beatify", "[beatify]")
{
    std::cout << "Start Testing" << std::endl;
    int const my_a = 1 - 2 + 1 + 1;
    int const my_b = 1;
    REQUIRE(my_a == my_b);
    CHECKED_IF(my_a == my_b)
    {
        std::cout << "Test Passed" << std::endl;
    }
    CHECKED_ELSE(my_a == my_b)
    {
        std::cout << "Test Failed" << std::endl;
    }
}