#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>
#include <list>

#include "../../src/concurrency/parallel_transform.h"

namespace {
    using namespace testing;
    using cppchallenge::concurrency::parallel_transform;

    TEST(ParallelTransformTest, NoDataShouldReturnEmpty) {
        auto empty_data = std::vector<int>{};

        auto result = parallel_transform(empty_data, [](const auto &el) {
            return 2 * el;
        });

        ASSERT_THAT(result, IsEmpty());
    }

    TEST(ParallelTransformTest, RandomAccessContainer) {
        auto input = std::vector{1, 2, 3, 4};

        auto result = parallel_transform(input, [](const auto &el) {
            return 2 * el;
        });

        ASSERT_THAT(result, ElementsAre(2, 4, 6, 8));
    }

    TEST(ParallelTransformTest, SequentialAccessContainer) {
        auto input = std::list{1, 2, 3, 4};

        auto result = parallel_transform(input, [](const auto &el) {
            return 2 * el;
        });

        ASSERT_THAT(result, ElementsAre(2, 4, 6, 8));
    }
}
