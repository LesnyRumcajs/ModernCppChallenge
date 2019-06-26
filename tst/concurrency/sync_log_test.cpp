
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <future>

#include "../../src/concurrency/sync_log.h"

namespace {
    using namespace testing;
    using cppchallenge::concurrency::SyncLogger;

    TEST(SyncLogTest, NoLogStreamEmpty) {
        std::stringstream result;
        SyncLogger logger(result);
        ASSERT_TRUE(result.str().empty());
    }

    TEST(SyncLogTest, SimpleLog) {
        std::stringstream result;

        SyncLogger logger(result);
        logger.log("test1");
        logger.log("test2");
        ASSERT_EQ(result.str(), "test1\ntest2\n");
    }

    TEST(SyncLogTest, MultithreadedLog) {
        std::stringstream result;
        SyncLogger logger(result);

        auto task1 = std::async(std::launch::async, [&logger]() {
            for (auto i{0u}; i < 10'000; ++i) {
                logger.log("11");
            }
        });

        auto task2 = std::async(std::launch::async, [&logger]() {
            for (auto i{0u}; i < 10'000; ++i) {
                logger.log("22");
            }
        });

        task1.wait();
        task2.wait();

        ASSERT_TRUE(result.str().find("121") == std::string::npos &&
                    result.str().find("212") == std::string::npos);
    }
}
