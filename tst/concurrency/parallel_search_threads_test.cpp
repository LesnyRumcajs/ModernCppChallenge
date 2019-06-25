#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/concurrency/parallel_search_threads.h"

namespace {
    using namespace testing;
    using cppchallenge::concurrency::parallel_max;
    using cppchallenge::concurrency::parallel_min;
    using cppchallenge::concurrency::parallel_sum;

   TEST(ParallelSearchMaxThreadTest, EmptyContainerShouldThrow) {
       auto input = std::vector<int>{};
       ASSERT_THROW(parallel_max(input.begin(), input.end()), std::invalid_argument);
   }

   TEST(ParallelSearchMaxThreadTest, SmallContainerShouldFindMaxValue) {
       auto input = std::vector{3,1,-6,6,5};
       auto result = parallel_max(input.begin(), input.end());

       ASSERT_EQ(result, 6);
   }

   TEST(ParallelSearchMaxThreadTest, LargeContainerShouldFindMaxValue) {
       auto input = std::vector<int>(42'420, 42);
       input[23'042] += 1;

       auto result = parallel_max(input.begin(), input.end());

       ASSERT_EQ(result, 43);
   }

   TEST(ParallelSearchMinThreadTest, EmptyContainerShouldThrow) {
       auto input = std::vector<int>{};
       ASSERT_THROW(parallel_min(input.begin(), input.end()), std::invalid_argument);
   }

   TEST(ParallelSearchMinThreadTest, SmallContainerShouldFindMinValue) {
       auto input = std::vector{3,1,-6,6,5};
       auto result = parallel_min(input.begin(), input.end());

       ASSERT_EQ(result, -6);
   }

   TEST(ParallelSearchMinThreadTest, LargeContainerShouldFindMinValue) {
       auto input = std::vector<int>(42'420, 42);
       input[23'042] -= 1;

       auto result = parallel_min(input.begin(), input.end());

       ASSERT_EQ(result, 41);
   }

   TEST(ParallelSearchSumThreadTest, EmptyContainerShouldThrow) {
       auto input = std::vector<int>{};
       ASSERT_THROW(parallel_sum(input.begin(), input.end()), std::invalid_argument);
   }

   TEST(ParallelSearchSumThreadTest, ShouldSumSmall) {
       auto input = std::vector{1,2,3};
       auto result = parallel_sum(input.begin(), input.end());

       ASSERT_EQ(result, 6);
   }
   TEST(ParallelSearchSumThreadTest, ShouldSumLarge) {
        auto input = std::vector<int>(42'420, 1);
        auto result = parallel_sum(input.begin(), input.end());

        ASSERT_EQ(result, 42'420);
    }
}
