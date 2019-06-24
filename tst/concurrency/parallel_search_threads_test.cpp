#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/concurrency/parallel_search_threads.h"

namespace {
    using namespace testing;
    using cppchallenge::concurrency::parallel_max;
    using cppchallenge::concurrency::parallel_min;

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

   TEST(ParallelSearchMinThreadTest, SmallContainerShouldFindMaxValue) {
       auto input = std::vector{3,1,-6,6,5};
       auto result = parallel_min(input.begin(), input.end());

       ASSERT_EQ(result, -6);
   }

   TEST(ParallelSearchMinThreadTest, LargeContainerShouldFindMaxValue) {
       auto input = std::vector<int>(42'420, 42);
       input[23'042] -= 1;

       auto result = parallel_min(input.begin(), input.end());

       ASSERT_EQ(result, 41);
   }}
