#include "../../src/server/utils/is_int.c"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("testingIsInt1", "[testingIsInt1]")
{
    char *str = strdup("42");

    REQUIRE(is_int(str) == true);
    free(str);
}

TEST_CASE("testingIsInt2", "[testingIsInt2]")
{
    char *str = strdup("42a");

    REQUIRE(is_int(str) == false);
    free(str);
}

TEST_CASE("testingIsInt3", "[testingIsInt3]")
{
    char *str = strdup("a42");

    REQUIRE(is_int(str) == false);
    free(str);
}

TEST_CASE("testingIsInt4", "[testingIsInt4]")
{
    char *str = strdup("42 ");

    REQUIRE(is_int(str) == false);
    free(str);
}

TEST_CASE("testingIsInt5", "[testingIsInt5]")
{
    char *str = strdup("-42");

    REQUIRE(is_int(str) == false);
    free(str);
}
