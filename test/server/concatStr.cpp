#include "../../src/server/utils/concat_str.c"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("testingConcatStr1", "[testingConcatStr1]")
{
    char *str = strdup("Hello");

    str = concat_str(str, "World");
    REQUIRE(!strcmp(str, "HelloWorld"));
    free(str);
}

TEST_CASE("testingConcatStr2", "[testingConcatStr2]")
{
    char *str = strdup("Hello");

    str = concat_str(str, "");
    REQUIRE(!strcmp(str, "Hello"));
    free(str);
}

TEST_CASE("testingConcatStr3", "[testingConcatStr3]")
{
    char *str = strdup("");

    str = concat_str(str, "World");
    REQUIRE(!strcmp(str, "World"));
    free(str);
}

TEST_CASE("testingConcatStr4", "[testingConcatStr4]")
{
    char *str = strdup("");

    str = concat_str(str, "");
    REQUIRE(!strcmp(str, ""));
    free(str);
}
