#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/concurrency/parallel_search_async.h"

namespace {
    using namespace testing;
    using cppchallenge::concurrency::parallel_async_max;
    using cppchallenge::concurrency::parallel_async_min;
    using cppchallenge::concurrency::parallel_async_sum;

    TEST(ParallelSearchMaxAsyncTest, EmptyContainerShouldThrow) {
        auto input = std::vector<int>{};
        ASSERT_THROW(parallel_async_max(input.begin(), input.end()), std::invalid_argument);
    }

    TEST(ParallelSearchMaxAsyncTest, SmallContainerShouldFindMaxValue) {
        auto input = std::vector{3, 1, -6, 6, 5};
        auto result = parallel_async_max(input.begin(), input.end());

        ASSERT_EQ(result, 6);
    }

    TEST(ParallelSearchMaxAsyncTest, LargeContainerShouldFindMaxValue) {
        auto input = std::vector<int>(42'420, 42);
        input[23'042] += 1;

        auto result = parallel_async_max(input.begin(), input.end());

        ASSERT_EQ(result, 43);
    }

    TEST(ParallelSearchMinAsyncTest, EmptyContainerShouldThrow) {
        auto input = std::vector<int>{};
        ASSERT_THROW(parallel_async_min(input.begin(), input.end()), std::invalid_argument);
    }

    TEST(ParallelSearchMinAsyncTest, SmallContainerShouldFindMinValue) {
        auto input = std::vector{3, 1, -6, 6, 5};
        auto result = parallel_async_min(input.begin(), input.end());

        ASSERT_EQ(result, -6);
    }

    TEST(ParallelSearchMinAsyncTest, LargeContainerShouldFindMinValue) {
        auto input = std::vector<int>(42'420, 42);
        input[23'042] -= 1;

        auto result = parallel_async_min(input.begin(), input.end());

        ASSERT_EQ(result, 41);
    }

    TEST(ParallelSearchSumAsyncTest, EmptyContainerShouldThrow) {
        auto input = std::vector<int>{};
        ASSERT_THROW(parallel_async_sum(input.begin(), input.end()), std::invalid_argument);
    }

    TEST(ParallelSearchSumAsyncTest, ShouldSumSmall) {
        auto input = std::vector{1, 2, 3};
        auto result = parallel_async_sum(input.begin(), input.end());

        ASSERT_EQ(result, 6);
    }

    TEST(ParallelSearchSumAsyncTest, ShouldSumLarge) {
        auto input = std::vector<int>(42'420, 1);
        auto result = parallel_async_sum(input.begin(), input.end());

        ASSERT_EQ(result, 42'420);
    }
}
