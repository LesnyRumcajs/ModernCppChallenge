#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/lang/temperature_scales.h"

namespace {
    using namespace cppchallenge::lang;
    TEST(AreEqualTest, NotEqual) {
        EXPECT_FALSE(are_equal(1,3,1));
        EXPECT_FALSE(are_equal(1,1.5));
        EXPECT_FALSE(are_equal(0,0.1));
        EXPECT_FALSE(are_equal(-1,1));
    }

    TEST(AreqEqualTest, Equal) {
        EXPECT_TRUE(are_equal(0,0));
        EXPECT_TRUE(are_equal(5,9,5));
        EXPECT_TRUE(are_equal(2,2.001));
        EXPECT_TRUE(are_equal(-1,-1.005, 0.01));
    }

    TEST(QuantityTest, ShouldCompareSameScale) {
        auto deg1 = 2.0_deg;
        auto deg2 = 3.0_deg;

        EXPECT_TRUE(deg1 < deg2);
        EXPECT_TRUE(deg1 <= deg2);
        EXPECT_TRUE(deg2 >= deg1);
        EXPECT_TRUE(deg1 < deg2);
        EXPECT_TRUE(deg1 != deg2);
        EXPECT_TRUE(deg1 == deg1);
        EXPECT_TRUE(deg1 <= deg1);
        EXPECT_TRUE(deg1 >= deg1);
    }

    TEST(QuantityTest, ShouldConvertBetweenCelsiusAndFahrenheit) {
        auto deg_cels{36.5_deg};
        auto deg_fahr{97.7_f};

        ASSERT_TRUE(deg_cels == temperature_cast<scale::celsius>(deg_fahr));
        ASSERT_TRUE(deg_fahr == temperature_cast<scale::fahrenheit>(deg_cels));
    }

    TEST(QuantityTest, ShouldConvertBetweenCelsiusAndKelvin) {
        auto deg_cels{36.5_deg};
        auto deg_kel{309.65_k};

        ASSERT_TRUE(deg_cels == temperature_cast<scale::celsius>(deg_kel));
        ASSERT_TRUE(deg_kel == temperature_cast<scale::kelvin>(deg_cels));
    }

    TEST(QuantityTest, ShouldConvertBetweenFahrenheitAndKelvin) {
        auto deg_fahr{97.7_f};
        auto deg_kel{309.65_k};

        ASSERT_TRUE(deg_fahr == temperature_cast<scale::fahrenheit>(deg_kel));
        ASSERT_TRUE(deg_kel == temperature_cast<scale::kelvin>(deg_fahr));
    }
}
