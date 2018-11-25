#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/string/join.h"
#include <list>
namespace {
    using namespace cppchallenge::string;
    using namespace testing;

    TEST(JoinTest, RandomAccessIterator_GivenEmptyContainerShouldReturnEmptyString) {
        ASSERT_THAT(join(std::vector<std::string>{}), IsEmpty());
    }

    TEST(JoinTest, RandomAccessIterator_GivenOneElementContainerShouldReturnElement) {
        ASSERT_EQ(join(std::vector<std::string>{"test"}), "test");
    }

    TEST(JoinTest, RandomAccessIterator_GivenMultipleElementsShouldReturnSeparatedElements) {
        ASSERT_EQ(join(std::vector<std::string>{"test", "fox"}), "test fox");
    }

    TEST(JoinTest, RandomAccessIterator_GivenMultipleElementsShouldReturnSeparatedElementsCustomSeparator) {
        ASSERT_EQ(join(std::vector<std::string>{"test", "fox"}, "--"), "test--fox");
    }

    TEST(JoinTest, BidirectionalIterator_GivenEmptyContainerShouldReturnEmptyString) {
        ASSERT_THAT(join(std::list<std::string>{}), IsEmpty());
    }

    TEST(JoinTest, BidirectionalIterator_GivenOneElementContainerShouldReturnElement) {
        ASSERT_EQ(join(std::list<std::string>{"test"}), "test");
    }

    TEST(JoinTest, BidirectionalIterator_GivenMultipleElementsShouldReturnSeparatedElements) {
        ASSERT_EQ(join(std::list<std::string>{"test", "fox"}), "test fox");
    }

    TEST(JoinTest, BidirectionalIterator_GivenMultipleElementsShouldReturnSeparatedElementsCustomSeparator) {
        ASSERT_EQ(join(std::list<std::string>{"test", "fox"}, "--"), "test--fox");
    }
}