#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/algorithms_data_structs/permutation.h"


namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::generate_permutations;

    TEST(PermutationTest, EmptyStringShouldReturnNone) {
        std::string input;
        ASSERT_THAT(generate_permutations<std::string>(input.begin(), input.end()), IsEmpty());
    }

    TEST(PermutationTest, SingleLetterStringShouldReturnSingleLetter) {
        std::string input{"a"};

        ASSERT_THAT(generate_permutations<std::string>(input.begin(), input.end()), ElementsAre("a"));
    }

    TEST(PermutationTest, MultipleLettersShouldReturnAllPermutations) {
        std::string input{"a 3"};

        ASSERT_THAT(generate_permutations<std::string>(input.begin(), input.end()),
                    UnorderedElementsAre("a 3", "a3 ", " 3a", " a3", "3a ", "3 a"));
    }

    TEST(PermutationTest, ShouldWorkOnOtherTypes) {
        std::vector<int> input{1, 2};
        std::vector<std::vector<int>> expected{{1, 2},
                                               {2, 1}};

        ASSERT_THAT(generate_permutations<std::vector<int>>(input.begin(), input.end()),
                    UnorderedElementsAre(expected[0], expected[1]));
    }
 }
