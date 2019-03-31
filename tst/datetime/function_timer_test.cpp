#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>

#include "../../src/datetime/function_timer.h"

namespace {
    using namespace testing;
    using cppchallenge::datetime::measure;
    using namespace std::chrono_literals;

    void empty_function() {
        ;
    }

    auto function_with_arguments(int, std::string) {
       return 42;
    }


    TEST(FunctionTimerTest, ShouldAcceptFunction) {
       auto empty_duration = measure(empty_function);
       auto args_duration = measure(function_with_arguments, 1, "test");

       ASSERT_TRUE(empty_duration < 1s);
       ASSERT_TRUE(args_duration < 1s);
    }

    TEST(FunctionTimerTest, ShouldAcceptClosure) {
        auto add = [](int a, int b) -> int { return a + b; };
        auto dummy = []() -> auto { return 42; };

        auto add_duration = measure(add, 2, 2);
        auto dummy_duration = measure(dummy);

        ASSERT_TRUE(add_duration < 1s);
        ASSERT_TRUE(dummy_duration < 1s);
    }

    TEST(FunctionTimerTest, ShouldCorrectlyMeasureExecutionTime) {
       auto fun = [](auto time) {
           std::this_thread::sleep_for(time);
       };

       auto duration = measure(fun, 20ms) + measure(fun, 42ms);

       ASSERT_TRUE(duration >= 62ms && duration <= 200ms);
    }
}
