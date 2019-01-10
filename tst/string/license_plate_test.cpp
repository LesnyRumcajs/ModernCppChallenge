#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/string/license_plate.h"

namespace {
    using namespace cppchallenge::string;
    using namespace testing;
    using namespace std::string_literals;

    TEST(LicensePlateValidationTest, GivenEmptyStringShouldReturnFalse) {
        EXPECT_FALSE(validate_plate(""s));
    }

    TEST(LicensePlateValidationTest, GivenCorrectPlateShouldReturnTrue) {
        EXPECT_TRUE(validate_plate("ABC-DEF 123"));
        EXPECT_TRUE(validate_plate("ABC-DEF 1234"s));
    }

    TEST(LicensePlateValidationTest, GivenIncorrectPlateShouldReturnTrue) {
        EXPECT_FALSE(validate_plate("DEF 123"));
        EXPECT_FALSE(validate_plate("ABC-DEF 12345"s));
    }

    TEST(LicensePlateExtractionTest, GivenEmptyStringShouldReturnEmptyCollection) {
        EXPECT_THAT(extract_plate(""), IsEmpty());
    }

    TEST(LicensePlateExtractionTest, GivenExactPlateShouldReturnIt) {
        EXPECT_THAT(extract_plate("ABC-DEF 123"), ElementsAre("ABC-DEF 123"));
    }

    TEST(LicensePlateExtractionTest, GivenMultiplePlatesShouldReturnThem) {
        EXPECT_THAT(extract_plate("ABC-DEF 123, ABC-DEF 1234|||OOO-III 000"), ElementsAre("ABC-DEF 123", "ABC-DEF 1234", "OOO-III 000"));
    }

    TEST(LicensePlateExtractionTest, GivenNoCorrectPlatesShouldReturnEmptyCollection) {
        EXPECT_THAT(extract_plate("LoremIpsumLoremIpsumLoremIpsum"), IsEmpty());
    }
}
