#include "../../src/server/utils/concat_word_array.c"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("testingConcatWordArray1", "[testingConcatWordArray1]")
{
    char **array = (char **) malloc(sizeof(char *) * 3);
    char *result = NULL;

    array[0] = strdup("Hello");
    array[1] = strdup("World");
    array[2] = NULL;
    result = concat_word_array(array);
    REQUIRE(strcmp(result, "Hello World") == 0);
    free(result);
    free(array[0]);
    free(array[1]);
    free(array);
}

TEST_CASE("testingConcatWordArray2", "[testingConcatWordArray2]")
{
    char **array = (char **) malloc(sizeof(char *) * 3);
    char *result = NULL;

    array[0] = strdup("");
    array[1] = strdup("World");
    array[2] = NULL;
    result = concat_word_array(array);
    REQUIRE(strcmp(result, " World") == 0);
    free(result);
    free(array[0]);
    free(array[1]);
    free(array);
}

TEST_CASE("testingConcatWordArray3", "[testingConcatWordArray3]")
{
    char **array = (char **) malloc(sizeof(char *) * 3);
    char *result = NULL;

    array[0] = strdup("Hello");
    array[1] = strdup("");
    array[2] = NULL;
    result = concat_word_array(array);
    REQUIRE(strcmp(result, "Hello ") == 0);
    free(result);
    free(array[0]);
    free(array[1]);
    free(array);
}

TEST_CASE("testingConcatWordArray4", "[testingConcatWordArray4]")
{
    char **array = (char **) malloc(sizeof(char *) * 4);
    char *result = NULL;

    array[0] = strdup("Hello");
    array[1] = strdup("World");
    array[2] = strdup("!");
    array[3] = NULL;
    result = concat_word_array(array);
    REQUIRE(strcmp(result, "Hello World !") == 0);
    free(result);
    free(array[0]);
    free(array[1]);
    free(array[2]);
    free(array);
}

TEST_CASE("testingConcatWordArray5", "[testingConcatWordArray5]")
{
    char **array = (char **) malloc(sizeof(char *) * 5);
    char *result = NULL;

    array[0] = strdup("Hello");
    array[1] = strdup("World");
    array[2] = strdup("!");
    array[3] = strdup("!");
    array[4] = NULL;
    result = concat_word_array(array);
    REQUIRE(strcmp(result, "Hello World ! !") == 0);
    free(result);
    free(array[0]);
    free(array[1]);
    free(array[2]);
    free(array[3]);
    free(array);
}
