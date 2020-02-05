#pragma once

#include <optional>
#include <vector>
#include <numeric>
#include "acceptance_system.h"

namespace cppchallenge::design_patterns {
    class DiscountType {
    public:
        [[nodiscard]] virtual double discountPercent(CurrencyUnit price, int  quantity) const noexcept = 0;
        virtual ~DiscountType() = default;
    };

    class FixedDiscount final : public DiscountType {
    public:
        explicit FixedDiscount(double fixedDiscount) : discount(fixedDiscount) {}

        [[nodiscard]] double discountPercent(const CurrencyUnit /*price*/, int  /*quantity*/) const noexcept override {
            return discount;
        }

    private:
        double discount;
    };

    class QuantityDiscount final : public DiscountType {
    public:
        QuantityDiscount(double discount, int  minQuantity) : discount(discount), minQuantity(minQuantity) {}

        [[nodiscard]] double discountPercent(const CurrencyUnit /*price*/, int  quantity) const noexcept override {
            return quantity >= minQuantity ? discount : 0.0;
        }

    private:
        double discount;
        int  minQuantity;
    };

    class PriceDiscount final : public DiscountType {
    public:
        PriceDiscount(double discount, CurrencyUnit minTotalPrice) : discount(discount), minTotalPrice(minTotalPrice) {}

        [[nodiscard]] double discountPercent(const CurrencyUnit price, int  quantity) const noexcept override {
            return (price * quantity >= minTotalPrice) ? discount : 0.0;
        }

    private:
        double discount;
        CurrencyUnit minTotalPrice;
    };

    struct Article {
        uint32_t id;
        CurrencyUnit price;
        std::unique_ptr<DiscountType> discount;
    };

    struct OrderLine {
        Article article;
        int  quantity;
        std::unique_ptr<DiscountType> discount;
    };

    struct Order {
        std::vector<OrderLine> orderLines;
        std::unique_ptr<DiscountType> discount;
    };


    class PriceCalculator {
    public:
        [[nodiscard]] virtual CurrencyUnit calculatePrice(const Order& order) const = 0;
        virtual ~PriceCalculator() = default;
    };

    class CumulativePriceCalculator : PriceCalculator {
    public:
        [[nodiscard]] CurrencyUnit calculatePrice(const Order& order) const override {
            auto orderTotal = std::accumulate(order.orderLines.begin(), order.orderLines.end(), 0, [](const auto sum, const auto& line) {
                auto linePrice = line.article.price * line.quantity;
                if (line.article.discount) {
                    linePrice -= linePrice * line.article.discount->discountPercent(line.article.price, line.quantity);
                }

                if (line.discount) {
                    linePrice -= linePrice * line.discount->discountPercent(line.article.price, line.quantity);
                }
                return sum + linePrice;
            });

            if (order.discount) {
                orderTotal -= orderTotal * order.discount->discountPercent(orderTotal, 1);
            }

            return orderTotal;
        }
    };
}