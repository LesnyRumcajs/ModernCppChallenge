#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/lang/container_minimum.h"

namespace {
    using namespace testing;
    using namespace cppchallenge::lang;

    TEST(MinTest, ShouldReturnMin) {
        ASSERT_EQ(min(1, 2), 1);
        ASSERT_EQ(min(0, 0), 0);
        ASSERT_EQ(min(-1, -3), -3);
    }

    TEST(MinCompTest, StlComparatorShouldReturnMin) {
        ASSERT_EQ(min(std::less<>(), 3, 2), 2);
    }

    TEST(MinCompTest, CustomComparatorShouldReturnMin) {
        auto abs_comp = [](auto el1, auto el2) {
            return std::abs(el1) < std::abs(el2);
        };
        ASSERT_EQ(min(abs_comp, -1, -5), -1);
    }

    TEST(ContainerMinTest, GivenUniqueElementsShouldReturnMinimum) {
        ASSERT_EQ(min(1, 2, 3, 4), 1);
        ASSERT_EQ(min(4, 3, 2, 1), 1);
        ASSERT_EQ(min(3, 2, 1, 4), 1);
    }

    TEST(ContainerMinTest, GivenNonUniqueElementsShouldReturnMinimum) {
        ASSERT_EQ(min(1, 2, 3, 1), 1);
        ASSERT_EQ(min(0, 0, 0, 1), 0);
        ASSERT_EQ(min(-1, -2, -3, -3), -3);
    }

    TEST(ContainerMinCompTest, GivenNonUniqueElementsCustomComparatorShouldReturnMinimum) {
        auto abs_comp = [](auto el1, auto el2) {
            return std::abs(el1) < std::abs(el2);
        };
        ASSERT_EQ(min(abs_comp, -3, -2, -1), -1);
    }

    TEST(ContainerMinCompTest, GivenNonUniqueElementsComparatorShouldReturnMinimum) {
        ASSERT_EQ(min(std::less<>(), 3, 2, 1), 1);
    }
}