#include "../../src/server/utils/calc_outbound.c"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("testingCalcOutbound1", "[testingCalcOutbound1]")
{
    int res = calc_outbound(17, 42);

    REQUIRE(res == 17);
}

TEST_CASE("testingCalcOutbound2", "[testingCalcOutbound2]")
{
    int res = calc_outbound(42, 17);

    REQUIRE(res == 25);
}

TEST_CASE("testingCalcOutbound3", "[testingCalcOutbound3]")
{
    int res = calc_outbound(-5, 13);

    REQUIRE(res == 8);
}

TEST_CASE("testingCalcOutbound4", "[testingCalcOutbound4]")
{
    int res = calc_outbound(11, 5);

    REQUIRE(res == 6);
}

TEST_CASE("testingCalcOutbound5", "[testingCalcOutbound5]")
{
    int res = calc_outbound(0, 0);

    REQUIRE(res == 0);
}

TEST_CASE("testingCalcOutbound6", "[testingCalcOutbound6]")
{
    int res = calc_outbound(0, 1);

    REQUIRE(res == 0);
}
