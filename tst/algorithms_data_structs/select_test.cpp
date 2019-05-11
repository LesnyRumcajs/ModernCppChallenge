#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/algorithms_data_structs/select.h"

namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::select;

    TEST(SelectTest, EmptyContainer) {
        auto input = std::vector<int>{};
        auto result = select(input, [](const auto& el) {
            return el;
        });

        ASSERT_THAT(result, IsEmpty());
    }

    TEST(SelectTest, SimpleType) {
        auto input = std::vector<int>{1,2,3,4};
        auto result = select(input, [](const auto& el) {
            return el;
        });

        ASSERT_THAT(result, ElementsAre(1,2,3,4));
    }

    TEST(SelectTest, SimpleTransformation) {
        auto input = std::vector<int>{1,2,3,4};
        auto result = select(input, [](const auto& el) {
            return std::to_string(el);
        });

        using namespace std::string_literals;
        ASSERT_THAT(result, ElementsAre("1"s, "2"s, "3"s, "4"s));
    }

    TEST(SelectTest, ComplexType) {
        auto input = std::vector<std::pair<std::string, int>>{{"one", 1}, {"two", 2}};
        auto result = select(input, [](const auto& el) {
           return el.first;
        });

        using namespace std::string_literals;
        ASSERT_THAT(result, ElementsAre("one"s, "two"s));
    }
}
