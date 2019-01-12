#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/stream_fs/pascal_triangle.h"

namespace {
    using namespace cppchallenge::streams_fs;
    TEST(PascalTriangleTest, GivenOneShoulPrintOne) {
        std::stringstream ss;
        print_pascal_triangle(ss, 1);

        ASSERT_EQ(ss.str(), "1\n");
    }

    TEST(PascalTriangleTest, GivenSmallNumberShouldPrintCorrectTriangle) {
        std::stringstream ss;
        print_pascal_triangle(ss, 2);

        ASSERT_EQ(ss.str(), " 1\n1 1\n");
    }

    TEST(PascalTriangleTest, GivenMediumNumberShouldPrintCorrectTriangle) {
        std::stringstream ss;
        print_pascal_triangle(ss, 5);
        ASSERT_EQ(ss.str(), "    1\n   1 1\n  1 2 1\n 1 3 3 1\n1 4 6 4 1\n");
    }
}
