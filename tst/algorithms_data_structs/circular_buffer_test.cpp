#include "../../src/algorithms_data_structs/circular_buffer.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::CircularBuffer;

    TEST(CircularBufferTest, EmptyBuffer) {
        CircularBuffer<int> buffer(5);

        ASSERT_TRUE(buffer.empty());
        ASSERT_EQ(buffer.size(), 0);
        ASSERT_EQ(buffer.capacity(), 5);
    }

    TEST(CircularBufferTest, ShouldThrowWhenPoppingEmpty) {
        CircularBuffer<int> buffer(5);

        ASSERT_THROW(buffer.pop(), std::runtime_error);
    }

    TEST(CircularBufferTest, PushElementsSimple) {
        CircularBuffer<int> buffer(5);
        buffer.push(1);
        buffer.push(2);
        buffer.push(3);

        ASSERT_FALSE(buffer.empty());
        ASSERT_EQ(buffer.pop(), 1);
        ASSERT_EQ(buffer.pop(), 2);
        ASSERT_EQ(buffer.pop(), 3);
    }

    TEST(CircularBufferTest, PushElementsPastCapacity) {
        CircularBuffer<int> buffer(3);
        buffer.push(1);
        buffer.push(2);
        buffer.push(3);
        ASSERT_TRUE(buffer.full());

        buffer.push(4);

        ASSERT_EQ(buffer.pop(), 2);
        ASSERT_EQ(buffer.pop(), 3);
        ASSERT_EQ(buffer.pop(), 4);
    }

    TEST(CircularBufferTest, IteratorDereferenceEmpty) {
        CircularBuffer<int> buffer(3);
        auto it = buffer.begin();

        ASSERT_THROW(*it, std::out_of_range);
    }

    TEST(CircularBufferTest, IteratorDereference) {
        CircularBuffer<int> buffer(3);
        buffer.push(3);
        buffer.push(2);
        buffer.push(1);
        auto it = buffer.begin();

        ASSERT_EQ(*it, 3);
        ++it;
        ASSERT_EQ(*it, 2);
        ++it;
        ASSERT_EQ(*it, 1);
        ++it;
        ASSERT_TRUE(it == buffer.end());
        ASSERT_THROW(++it, std::out_of_range);
    }

    TEST(CircularBufferTest, IteratorArrowOperator) {
        CircularBuffer<std::string> buffer(3);
        buffer.push("test");
        ASSERT_EQ(4, buffer.begin()->length());
    }
}
