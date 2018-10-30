#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/lang/BasicArray.h"

namespace {
    using namespace cppchallenge::lang;

    TEST(BasicArrayTest, ShouldConstructArrayWithInitialization) {
        BasicArray<int, 2, 3> array{1, 2, 3, 4, 5, 6};
    }

    TEST(BasicArrayTest, ShouldAccessElementsInitialized) {
        BasicArray<int, 2, 3> array{1, 2, 3, 4, 5, 6};
        ASSERT_EQ(array(1, 2), 6);
        ASSERT_EQ(array(0, 0), 1);
        ASSERT_EQ(array(1, 0), 4);
    }

    TEST(BasicArrayTest, ShouldAccessElementsNotInitialized) {
        BasicArray<int, 1, 1> array;
        ASSERT_EQ(array(0, 0), 0);
    }

    TEST(BasicArrayTest, ShouldThrowWhenAccessedOutOfRange) {
        BasicArray<int, 1, 1> array;
        ASSERT_THROW(array(1, 1), std::out_of_range);
    }

    TEST(BasicArrayTest, ShouldModifyElementsOfExistingArray) {
        BasicArray<int, 1, 1> array;
        array(0, 0) = 1;
        ASSERT_EQ(array(0, 0), 1);
    }

    TEST(BasicArrayTest, ShouldReturnEmptyWhenArrayEmpty) {
        ASSERT_TRUE((BasicArray<int, 0, 0>().empty()));
    }

    TEST(BasicArrayTest, ShouldCorrectlyFillArray) {
        BasicArray<int, 2, 2> array;
        array.fill(1);
        ASSERT_EQ(array.at(0, 0), 1);
        ASSERT_EQ(array.at(0, 1), 1);
        ASSERT_EQ(array.at(1, 0), 1);
        ASSERT_EQ(array.at(1, 1), 1);
    }

    TEST(BasicArrayTest, ShouldBeAbleToMove) {
        BasicArray<int, 2, 2> array_to_move{1, 2, 3, 4};

        BasicArray<int, 2, 2> array_from_move{std::move(array_to_move)};
        ASSERT_EQ(array_from_move.at(0, 0), 1);
        ASSERT_EQ(array_from_move.at(0, 1), 2);
        ASSERT_EQ(array_from_move.at(1, 0), 3);
        ASSERT_EQ(array_from_move.at(1, 1), 4);
    }

    TEST(BasicArray, ShouldIterateOverElementsNoModify) {
        BasicArray<int, 2, 2> array{0, 1, 2, 3};

        int counter{};
        for (BasicArray<int, 2, 2>::const_iterator it = array.begin(); it != array.end(); ++it) {
            ASSERT_EQ(*it, counter++);
        }
    }

    TEST(BasicArray, ShouldIterateOverElementsModify) {
        BasicArray<int, 2, 2> array{0, 1, 2, 3};

        int counter{};
        for (BasicArray<int, 2, 2>::iterator it = array.begin(); it != array.end(); ++it) {
            ASSERT_EQ(*it, counter++);
            *it = 42;
            ASSERT_EQ(*it, 42);
        }
    }
}