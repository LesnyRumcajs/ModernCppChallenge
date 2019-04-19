#include "../../src/algorithms_data_structs/priority_queue.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::PriorityQueue;

    TEST(PriorityQueueTest, Size) {
        PriorityQueue<int> queue;
        ASSERT_EQ(queue.size(), 0);

        queue.emplace(2);
        ASSERT_EQ(queue.size(), 1);
    }

    TEST(PriorityQueueTest, Empty) {
        PriorityQueue<int> queue;
        ASSERT_TRUE(queue.empty());

        queue.emplace(2);
        ASSERT_FALSE(queue.empty());
    }

    TEST(PriorityQueueTest, SortedInsert) {
        PriorityQueue<int> queue;
        queue.emplace(1);
        queue.emplace(2);
        queue.emplace(3);
        queue.emplace(5);

        ASSERT_EQ(queue.top(), 5);

        ASSERT_EQ(queue.pop(), 5);
        ASSERT_EQ(queue.pop(), 3);
        ASSERT_EQ(queue.pop(), 2);
        ASSERT_EQ(queue.pop(), 1);
    }

    TEST(PriorityQueueTest, UnsortedInsert) {
        PriorityQueue<int> queue;
        queue.push(3);
        queue.push(5);
        queue.push(2);
        queue.push(1);

        ASSERT_EQ(queue.top(), 5);

        ASSERT_EQ(queue.pop(), 5);
        ASSERT_EQ(queue.pop(), 3);
        ASSERT_EQ(queue.pop(), 2);
        ASSERT_EQ(queue.pop(), 1);
    }

    TEST(PriorityQueueTest, FromInitializerList) {
        PriorityQueue<std::string> queue{"the", "quick", "brown", "fox"};

        ASSERT_EQ(queue.top(), "the");

        ASSERT_EQ(queue.pop(), "the");
        ASSERT_EQ(queue.pop(), "quick");
        ASSERT_EQ(queue.pop(), "fox");
        ASSERT_EQ(queue.pop(), "brown");
    }

    TEST(PriorityQueueTest, CustomComparer) {
        PriorityQueue<int, std::greater<>> queue;

        queue.push(3);
        queue.push(5);
        queue.push(2);
        queue.push(1);

        ASSERT_EQ(queue.top(), 1);

        ASSERT_EQ(queue.pop(), 1);
        ASSERT_EQ(queue.pop(), 2);
        ASSERT_EQ(queue.pop(), 3);
        ASSERT_EQ(queue.pop(), 5);
    }
}
