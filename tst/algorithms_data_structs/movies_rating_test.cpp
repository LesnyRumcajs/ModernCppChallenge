#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/algorithms_data_structs/movies_rating.h"

namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::truncated_mean;
    using cppchallenge::algorithms_data_structs::average_movies;

    TEST(TruncatedMeanTest, NoElementsShouldReturnZero) {
        auto result = truncated_mean(std::vector<int>{}, 0.05);
        ASSERT_DOUBLE_EQ(result, 0.0);
    }

    TEST(TruncatedMeanTest, ZeroPercentTruncationShouldNotTruncate) {
        auto result = truncated_mean(std::vector{1,2,3}, 0.0);
        ASSERT_DOUBLE_EQ(result, 2.0);
    }

    TEST(TruncatedMeanTest, GivenNonZeroPercentShouldTruncate) {
        auto result = truncated_mean(std::vector{1,5,10}, 0.33);
        ASSERT_DOUBLE_EQ(result, 5.0);
    }

    TEST(TruncatedMeanTest, ComplexSortedValues) {
        auto result = truncated_mean(std::vector{1,2,3,4,5,6,7,8,9,10}, 0.1);
        ASSERT_DOUBLE_EQ(result, 5.5);
    }

    TEST(TruncatedMeanTest, ComplexUnsortedValues) {
       auto result = truncated_mean(std::vector{10,8,9,7,5,4,3,6,1,2}, 0.1);
       ASSERT_DOUBLE_EQ(result, 5.5);
    }

    TEST(AverageMoviesTest, NoMoviesNoResult) {
        std::vector<std::pair<std::string, std::vector<int>>> movies;
        auto result = average_movies(movies);
        ASSERT_THAT(result, IsEmpty());
    }

    TEST(AverageMoviesTest, SingleMovieCorrectAverage) {
        std::vector<std::pair<std::string, std::vector<int>>> movies{{"test1", {1,2,3,4}}};
        auto result = average_movies(movies);
        ASSERT_THAT(result, ElementsAre(Pair("test1", 2.5)));
    }

    TEST(AverageMoviesTest, MultipleMoviesCorrectAverage) {
        std::vector<std::pair<std::string, std::vector<int>>> movies{{"test1", {1,2,3,4}},
                                                                     {"test2", {10,8,9,7,5,4,3,6,1,2}}};
        auto result = average_movies(movies);
        ASSERT_THAT(result, ElementsAre(Pair("test1", 2.5),
                                        Pair("test2", 5.5))
                                        );
    }
}
