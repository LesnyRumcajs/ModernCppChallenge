#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/design_patterns/social_insurance_number_generator.h"

namespace {
    using namespace testing;
    using namespace cppchallenge::design_patterns;

    TEST(SocialInsuranceNumberGeneratorTest, ValidateCountries) {
        SocialNumberGeneratorFactory factory;
        ASSERT_NE(factory.getGenerator("northeria"), nullptr);
        ASSERT_NE(factory.getGenerator("southeria"), nullptr);

        ASSERT_THROW((void)factory.getGenerator("san escobar"), std::invalid_argument);
    }

    TEST(SocialInsuranceNumberGeneratorTest, ShouldGenerateDifferentForNortheria) {
        NortheriaSocialNumberGenerator generator;
        for (auto i(0U); i < 100; ++i) {
            auto number1 = generator.generate(Sex::male, 2019, 13, 10);
            auto number2 = generator.generate(Sex::male, 2019, 13, 10);

            ASSERT_NE(number1, number2);
        }
    }
    TEST(SocialInsuranceNumberGeneratorTest, ShouldGenerateDifferentForSoutheria) {
        SoutheriaSocialNumberGenerator generator;
        for (auto i(0U); i < 100; ++i) {
            auto number1 = generator.generate(Sex::male, 2019, 13, 10);
            auto number2 = generator.generate(Sex::male, 2019, 13, 10);

            ASSERT_NE(number1, number2);
        }
    }
}
