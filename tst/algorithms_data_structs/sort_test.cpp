#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <list>
#include "../../src/algorithms_data_structs/sort.h"

namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::quick_sort;

    TEST(SortTest, NoElementsShouldDoNothing) {
        auto input = std::list<int>{};
        quick_sort(input.begin(), input.end());

        ASSERT_THAT(input, IsEmpty());
    }

    TEST(SortTest, SingleElementShouldDoNothing) {
        auto input = std::vector{1};
        quick_sort(input.begin(), input.end());

        ASSERT_THAT(input, ElementsAre(1));
    }

    TEST(SortTest, SortedContainerShouldDoNothing) {
        auto input = std::vector{1,2,3};
        quick_sort(input.begin(), input.end());

        ASSERT_THAT(input, ElementsAre(1,2,3));
    }

    TEST(SortTest, UnsortedContainerShouldSort) {
        auto input = std::vector{3,1,2};
        quick_sort(input.begin(), input.end());

        ASSERT_THAT(input, ElementsAre(1,2,3));
    }

    TEST(SortTest, UnsortedCustomComparator) {
        auto input = std::vector{3,1,2};
        quick_sort(input.begin(), input.end(), std::greater<>());

        ASSERT_THAT(input, ElementsAre(3,2,1));
    }

    TEST(SortTest, UnsortedWithLambda) {
        auto input = std::vector{3,1,2};
        quick_sort(input.begin(), input.end(), [](const auto el1, const auto el2) {
            return el1 > el2;
        });

        ASSERT_THAT(input, ElementsAre(3,2,1));
    }
}
