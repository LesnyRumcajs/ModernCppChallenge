#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <list>

#include "../../src/lang/contains_helpers.h"

namespace {
    using namespace testing;
    using namespace cppchallenge::lang;

    TEST(ContainsTest, GivenEmptyShouldReturnFalse) {
        ASSERT_FALSE(contains(std::vector<int>{}, 1));
        ASSERT_FALSE(contains(std::list<std::string>{}, "test"));
    }

    TEST(ContainsTest, GivenContainerWithValueShouldReturnTrue) {
        ASSERT_TRUE(contains(std::vector<int>{1, 2, 3, 4}, 3));
        ASSERT_TRUE(contains(std::list<std::string>{"test1", "test2"}, "test2"));
    }

    TEST(ContainsTest, GivenContainerWithoutValueShouldReturnFalse) {
        ASSERT_FALSE(contains(std::vector<int>{1, 2, 3, 4}, 5));
        ASSERT_FALSE(contains(std::list<std::string>{"test1", "test2"}, "test3"));
    }

    TEST(ContainsAnyTest, GivenEmptyContainerShouldReturnFalse) {
        ASSERT_FALSE(contains_any(std::vector<int>{}, 1, 2));
    }

    TEST(ContainsAnyTest, GivenNoneOfTheValuesShouldReturnFalse) {
        ASSERT_FALSE(contains_any(std::vector<int>{1, 2}, 3, 4, 5));
    }

    TEST(ContainsAnyTest, GivenAllOfTheValuesShouldReturnTrue) {
        ASSERT_TRUE(contains_any(std::vector<int>{1, 2, 3}, 1, 2, 3));
    }

    TEST(ContainsAnyTest, GivenSomeOfTheValuesShouldReturnTrue) {
        ASSERT_TRUE(contains_any(std::vector<int>{1, 2, 3}, 4, 5, 6, 1));
    }

    TEST(ContainsAllTest, GivenEmptyContainerShouldReturnFalse) {
        ASSERT_FALSE(contains_all(std::vector<int>{}, 1, 2));
    }

    TEST(ContainsAllTest, GivenNoneOfTheValuesShouldReturnFalse) {
        ASSERT_FALSE(contains_all(std::vector<int>{1, 2}, 3, 4, 5));
    }

    TEST(ContainsAllTest, GivenAllOfTheValuesShouldReturnTrue) {
        ASSERT_TRUE(contains_all(std::vector<int>{1, 2, 3}, 1, 2, 3));
    }

    TEST(ContainsAllTest, GivenSomeOfTheValuesShouldReturnFalse) {
        ASSERT_FALSE(contains_all(std::vector<int>{1, 2, 3}, 4, 5, 6, 1));
    }

    TEST(ContainsNoneTest, GivenEmptyContainerShouldReturnTrue) {
        ASSERT_TRUE(contains_none(std::vector<int>{}, 1, 2));
    }

    TEST(ContainsNoneTest, GivenNoneOfTheValuesShouldReturnTrue) {
        ASSERT_TRUE(contains_none(std::vector<int>{1, 2}, 3, 4, 5));
    }

    TEST(ContainsNoneTest, GivenAllOfTheValuesShouldReturnFalse) {
        ASSERT_FALSE(contains_none(std::vector<int>{1, 2, 3}, 1, 2, 3));
    }

    TEST(ContainsNoneTest, GivenSomeOfTheValuesShouldReturnFalse) {
        ASSERT_FALSE(contains_none(std::vector<int>{1, 2, 3}, 4, 5, 6, 1));
    }

}