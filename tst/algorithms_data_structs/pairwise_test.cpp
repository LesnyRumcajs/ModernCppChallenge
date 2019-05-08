#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/algorithms_data_structs/pairwise.h"

namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::to_pairs;

    TEST(PairwiseTest, NoDataShouldReturnEmpty) {
        auto result = to_pairs(std::vector<int>{});
        ASSERT_THAT(result, IsEmpty());
    }

    TEST(PairwiseTest, EvenShouldMakePairs) {
        auto result = to_pairs(std::vector{1,2,3,4});
        ASSERT_THAT(result, ElementsAre(Pair(1,2), Pair(3,4)));
    }

    TEST(PairwiseTest, OddShouldMakePairsAndIgnoreLast) {
        auto result = to_pairs(std::vector{1,2,3,4,5});
        ASSERT_THAT(result, ElementsAre(Pair(1,2), Pair(3,4)));
    }

    TEST(PairwiseTest, ComplexTypes) {
        using namespace std::string_literals;
        auto result = to_pairs(std::vector{"a"s, "b"s, "c"s, "d"s, "e"s});
        ASSERT_THAT(result, ElementsAre(Pair("a"s, "b"s), Pair("c"s, "d"s)));
    }
}

