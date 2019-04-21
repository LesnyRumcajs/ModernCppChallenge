#include "../../src/algorithms_data_structs/text_histogram.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::create_histogram;

    TEST(TextHistogramTest, EmptyInputShouldReturnEmptyHistogram) {
        ASSERT_THAT(create_histogram(""), IsEmpty());
    }

    TEST(TextHistogramTest, NoValidCharactersShouldReturnEmpty) {
        ASSERT_THAT(create_histogram(" 132 __ $$ !@#$%^*&)"), IsEmpty());
    }

    TEST(TextHistogramTest, AllLettersTheSameShouldReturnSingleItem) {
        auto result = create_histogram("aaaa");
        ASSERT_EQ(result.size(), 1);
        ASSERT_EQ(result[0].first, 'a');
        ASSERT_NEAR(result[0].second, 1.0, 0.001);
    }

    TEST(TextHistogramTest, ComplexHistograms) {
        auto result = create_histogram("aaabb eefff");
        ASSERT_EQ(result.size(), 4);

        ASSERT_EQ(result[0].first, 'a');
        ASSERT_NEAR(result[0].second, 0.3, 0.001);

        ASSERT_EQ(result[1].first, 'f');
        ASSERT_NEAR(result[1].second, 0.3, 0.001);

        ASSERT_EQ(result[2].first, 'b');
        ASSERT_NEAR(result[2].second, 0.2, 0.001);

        ASSERT_EQ(result[3].first, 'e');
        ASSERT_NEAR(result[3].second, 0.2, 0.001);
    }
}