#include "../../src/algorithms_data_structs/phone_numbers_filter.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::filter_phone_numbers;
    using cppchallenge::algorithms_data_structs::starts_with_code;
    using cppchallenge::algorithms_data_structs::is_valid_length;

    TEST(PhoneNumbersFilterTest, ChecksIfValidNumberLength) {
        ASSERT_FALSE(is_valid_length(""));
        ASSERT_FALSE(is_valid_length("123456789"));
        ASSERT_TRUE(is_valid_length("48123456789"));
    }

    TEST(PhoneNumbersFilterTest, ChecksIfStartsWithCode) {
        ASSERT_FALSE(starts_with_code("+43123", "44"));
        ASSERT_FALSE(starts_with_code("123", "31"));
        ASSERT_TRUE(starts_with_code("123", "12"));
        ASSERT_TRUE(starts_with_code("+44123", "44"));
    }

    TEST(PhoneNumbersFilterTest, GivenEmptyReturnsEmpty) {
        auto result = filter_phone_numbers({}, "44");
        ASSERT_THAT(result, IsEmpty());
    }

    TEST(PhoneNumbersFilterTest, GivenAllCorrectShouldReturnAll) {
        auto result = filter_phone_numbers({"+44123456789", "44123456789"}, "44");
        ASSERT_THAT(result, ElementsAre("+44123456789", "44123456789"));
    }

    TEST(PhoneNumbersFilterTest, GivenSomeCorrectShouldReturnThem) {
        auto result = filter_phone_numbers({"+44123456789", "12", "", "43123456789", "44123456789"}, "44");
        ASSERT_THAT(result, ElementsAre("+44123456789", "44123456789"));
    }
}
