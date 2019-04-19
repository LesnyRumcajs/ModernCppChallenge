#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>
#include "../../src/algorithms_data_structs/double_buffer.h"

namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::DoubleBuffer;

    TEST(DoubleBufferTest, SingleThreadWriteRead) {
        DoubleBuffer<int> buff(10);
        std::vector<int> to_write{1, 2, 3};
        buff.write(to_write.data(), to_write.size());

        ASSERT_EQ(buff[0], 1);
        ASSERT_EQ(buff[1], 2);
        ASSERT_EQ(buff[2], 3);

        std::vector<int> to_read(3);
        buff.read(to_read.begin(), to_read.size());
        ASSERT_EQ(to_write, to_read);
    }

    TEST(DoubleBufferTest, WritingPastCapacity) {
        DoubleBuffer<int> buff(1);
        std::vector<int> to_write{1, 2};
        buff.write(to_write.data(), to_write.size());

        std::vector<int> result(3);
        buff.read(result.begin(), result.size());

        std::vector<int> expected{1, 0, 0};
        ASSERT_EQ(expected, result);
    }

    TEST(DoubleBufferTest, MultithreadedWriteRead) {
        DoubleBuffer<int> buff(10);
        std::vector<int> first_read(10);
        std::thread consumer([&buff, &first_read] {
            // constantly check if buffer has changed
            while (buff[0] == 0) {}
            buff.read(first_read.begin(), first_read.size());
        });

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(10ms);

        std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::thread producer([&buff, &expected] {
            buff.write(expected.data(), expected.size());
        });

        consumer.join();
        producer.join();

        ASSERT_EQ(first_read, expected);
    }
}
