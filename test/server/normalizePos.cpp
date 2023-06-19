#include <iostream>
#include "../../src/server/implementation/normalize_pos.c"
#include "../../src/server/utils/calc_outbound.c"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("testingPosNormalization1", "[testingPosNormalization1]")
{
    pos_t *pos = (pos_t *) malloc(sizeof(pos_t));
    const int width = 10;
    const int height = 10;

    pos->x = 13;
    pos->y = -2;
    normalize_pos(pos, width, height);
    REQUIRE(pos->x == 3);
    REQUIRE(pos->y == 8);
    free(pos);
}

TEST_CASE("testingPosNormalization2", "[testingPosNormalization2]")
{
    pos_t *pos = (pos_t *) malloc(sizeof(pos_t));
    const int width = 10;
    const int height = 10;

    pos->x = 4;
    pos->y = 10;
    normalize_pos(pos, width, height);
    REQUIRE(pos->x == 4);
    REQUIRE(pos->y == 0);
    free(pos);
}

TEST_CASE("testingPosNormalization3", "[testingPosNormalization3]")
{
    pos_t *pos = (pos_t *) malloc(sizeof(pos_t));
    const int width = 10;
    const int height = 10;

    pos->x = 0;
    pos->y = 0;
    normalize_pos(pos, width, height);
    REQUIRE(pos->x == 0);
    REQUIRE(pos->y == 0);
    free(pos);
}

TEST_CASE("testingPosNormalization4", "[testingPosNormalization4]")
{
    pos_t *pos = (pos_t *) malloc(sizeof(pos_t));
    const int width = 10;
    const int height = 10;

    pos->x = 10;
    pos->y = 10;
    normalize_pos(pos, width, height);
    REQUIRE(pos->x == 0);
    REQUIRE(pos->y == 0);
    free(pos);
}
