#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/algorithms_data_structs/phone_numbers_transform.h"


namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::phone_numbers_transform;
    using cppchallenge::algorithms_data_structs::phone_number_transform;

    TEST(PhoneNumbersTransformTest, EmptyContainerShouldReturnEmpty) {
        std::vector<std::string> testee;
        phone_numbers_transform(testee.begin(), testee.end(), "44");
        ASSERT_THAT(testee, IsEmpty());
    }

    TEST(PhoneNumbersTransformTest, SampleTransformations) {
        auto testee = std::vector<std::string>{"07555 123456", "07555123456", "+447555123456", "447555123456", "7555123456"};
        phone_numbers_transform(testee.begin(), testee.end(), "44");

        for (const auto& number : testee) {
            ASSERT_EQ(number, "+447555123456");
        }
    }

    TEST(PhoneNumbersTransformTest, DifferentCountryShouldNotModify) {
        auto result = phone_number_transform("+48123456789", "44");
        ASSERT_EQ(result, "+48123456789");
    }
}
