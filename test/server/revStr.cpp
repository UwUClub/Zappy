#include "../../src/server/utils/revstr.c"
#include <string.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("testingRevStr1", "[testingRevStr1]")
{
    char *res = strdup("Hello World");

    res = revstr(res);
    REQUIRE(strcmp(res, "dlroW olleH") == 0);
    free(res);
}

TEST_CASE("testingRevStr2", "[testingRevStr2]")
{
    char *res = strdup("Hello World");

    res = revstr(res);
    REQUIRE(strcmp(res, "_dlroW olleH"));
    free(res);
}

TEST_CASE("testingRevStr3", "[testingRevStr3]")
{
    char *res = strdup("Hello World");

    res = revstr(res);
    REQUIRE(strcmp(res, "dlroW olleH_"));
    free(res);
}
