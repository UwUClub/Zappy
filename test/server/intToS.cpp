#include "../../src/server/utils/int_to_s.c"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("testingIntToS1", "[testingIntToS1]")
{
    char *res = int_to_s(42);

    REQUIRE(strcmp(res, "42") == 0);
    free(res);
}

TEST_CASE("testingIntToS2", "[testingIntToS2]")
{
    char *res = int_to_s(0);

    REQUIRE(strcmp(res, "0") == 0);
    free(res);
}

TEST_CASE("testingIntToS3", "[testingIntToS3]")
{
    char *res = int_to_s(-42);

    REQUIRE(strcmp(res, "-42") == 0);
    free(res);
}
