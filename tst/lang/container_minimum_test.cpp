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
}