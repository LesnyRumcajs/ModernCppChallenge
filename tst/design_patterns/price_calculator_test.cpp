#include <gtest/gtest.h>
#include "../../src/design_patterns/price_calculator.h"

namespace {
    using namespace testing;
    using namespace cppchallenge::design_patterns;

    TEST(PriceCalculator, NothingMakesNothing) {
        auto calculator = std::make_unique<CumulativePriceCalculator>();
        auto order = Order();

        ASSERT_EQ(calculator->calculatePrice(order), 0);
    }

    TEST(PriceCalculator, NoDiscounts) {
        auto calculator = std::make_unique<CumulativePriceCalculator>();
        auto order = Order();
        order.orderLines.push_back(OrderLine{Article{0, 1, nullptr}, 2, nullptr});
        ASSERT_EQ(calculator->calculatePrice(order), 2);
    }

    TEST(PriceCalculator, OnlyOrderDiscount) {
        auto calculator = std::make_unique<CumulativePriceCalculator>();
        auto order = Order();
        order.orderLines.push_back(OrderLine{Article{0, 1, nullptr}, 10, nullptr});
        order.discount = std::make_unique<FixedDiscount>(0.1);
        ASSERT_EQ(calculator->calculatePrice(order), 9);
    }

    TEST(PriceCalculator, QuantityDiscount) {
        auto calculator = std::make_unique<CumulativePriceCalculator>();
        auto order = Order();
        order.orderLines.push_back(OrderLine{Article{0, 1, nullptr}, 10, std::make_unique<QuantityDiscount>(0.1, 10)});
        ASSERT_EQ(calculator->calculatePrice(order), 9);
    }

    TEST(PriceCalculator, TotalProductLineDiscount) {
        auto calculator = std::make_unique<CumulativePriceCalculator>();
        auto order = Order();
        order.orderLines.push_back(OrderLine{Article{0, 10, nullptr}, 10, std::make_unique<PriceDiscount>(0.1, 100)});
        ASSERT_EQ(calculator->calculatePrice(order), 90);
    }

    TEST(PriceCalculator, FixedArticlePrice) {
        auto calculator = std::make_unique<CumulativePriceCalculator>();
        auto order = Order();
        order.orderLines.push_back(OrderLine{Article{0, 10, std::make_unique<FixedDiscount>(0.1)}, 10, nullptr});
        ASSERT_EQ(calculator->calculatePrice(order), 90);
    }

    TEST(PriceCalculator, MultipleProducts) {
        auto calculator = std::make_unique<CumulativePriceCalculator>();
        auto order = Order();
        order.orderLines.push_back(OrderLine{Article{0, 10, std::make_unique<FixedDiscount>(0.1)}, 10, nullptr});
        order.orderLines.push_back(OrderLine{Article{1, 10, nullptr}, 10, nullptr});
        ASSERT_EQ(calculator->calculatePrice(order), 190);
    }
}