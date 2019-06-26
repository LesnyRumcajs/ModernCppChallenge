#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/concurrency/parallel_sort.h"

namespace {
    using namespace testing;
    using cppchallenge::concurrency::parallel_quick_sort;

    TEST(ParallelSortTest, NoElementsShouldDoNothing) {
        auto input = std::vector<int>{};
        parallel_quick_sort(input.begin(), input.end());

        ASSERT_THAT(input, IsEmpty());
    }

    TEST(ParallelSortTest, SingleElementShouldDoNothing) {
        auto input = std::vector{1};
        parallel_quick_sort(input.begin(), input.end());

        ASSERT_THAT(input, ElementsAre(1));
    }

    TEST(ParallelSortTest, SortedContainerShouldDoNothing) {
        auto input = std::vector{1, 2, 3};
        parallel_quick_sort(input.begin(), input.end());

        ASSERT_THAT(input, ElementsAre(1, 2, 3));
    }

    TEST(ParallelSortTest, UnsortedContainerShouldSort) {
        auto input = std::vector{3, 1, 2};
        parallel_quick_sort(input.begin(), input.end());

        ASSERT_THAT(input, ElementsAre(1, 2, 3));
    }

    TEST(ParallelSortTest, UnsortedCustomComparator) {
        auto input = std::vector{3, 1, 2};
        parallel_quick_sort(input.begin(), input.end(), std::greater<>());

        ASSERT_THAT(input, ElementsAre(3, 2, 1));
    }

    TEST(ParallelSortTest, UnsortedWithLambda) {
        auto input = std::vector{3, 1, 2};
        parallel_quick_sort(input.begin(), input.end(), [](const auto el1, const auto el2) {
            return el1 > el2;
        });

        ASSERT_THAT(input, ElementsAre(3, 2, 1));
    }
}
