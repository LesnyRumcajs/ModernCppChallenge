#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/algorithms_data_structs/most_frequent.h"

namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::most_frequent;

    TEST(MostFrequentTest, EmptyInputShouldReturnEmpty) {
        std::vector<int> input;
        ASSERT_THAT(most_frequent(input), IsEmpty());
    }

    TEST(MostFrequentTest, UniqueInputShouldReturnAll) {
        std::vector<int> input{3, 1, 2};
        auto result = most_frequent(input);

        ASSERT_THAT(result, UnorderedElementsAre(Pair(3, 1), Pair(1, 1), Pair(2, 1)));
    }

    TEST(MostFrequentTest, AllTheSameShouldReturnSingle) {
        std::vector<std::string> input{"test", "test", "test"};
        auto result = most_frequent(input);

        ASSERT_THAT(result, ElementsAre(Pair("test", 3)));
    }

    TEST(MostFrequentTest, MixedShouldReturnMostFrequent) {
        std::vector<int> input{3, -1, 2, 5, -1, 2, 3, 3};
        auto result = most_frequent(input);

        ASSERT_THAT(result, ElementsAre(Pair(3, 3)));
    }
}