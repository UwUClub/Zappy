#include "../../src/server/utils/is_ip.c"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("testingIsIp1", "[testingIsIp1]")
{
    char *str = strdup("127.0.0.1");

    REQUIRE(is_ip(str) == true);
    free(str);
}

TEST_CASE("testingIsIp2", "[testingIsIp2]")
{
    char *str = strdup("127.0.0cenestpasuneip");

    REQUIRE(is_ip(str) == false);
    free(str);
}

TEST_CASE("testingIsIp3", "[testingIsIp3]")
{
    char *str = strdup("0.0.0.0.");

    REQUIRE(is_ip(str) == false);
    free(str);
}

TEST_CASE("testingIsIp4", "[testingIsIp4]")
{
    char *str = strdup(".0.0.0.0");

    REQUIRE(is_ip(str) == false);
    free(str);
}

TEST_CASE("testingIsIp5", "[testingIsIp5]")
{
    char *str = strdup("73.28.744.947");

    REQUIRE(is_ip(str) == true);
    free(str);
}
