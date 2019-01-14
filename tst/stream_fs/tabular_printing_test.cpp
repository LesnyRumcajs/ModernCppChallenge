#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/stream_fs/tabular_printing.h"

namespace {
    using namespace std::string_literals;
    using namespace cppchallenge::stream_fs;
    using namespace testing;

    TEST(PrintProcessesTest, GivenEmptyListShouldPrintNothing) {
        std::stringstream result;
        print_processes(result, {});

        ASSERT_THAT(result.str(), IsEmpty());
    }

    TEST(PrintProcessesTest, GivenSingleProcessShouldCorrectlyPrint) {
        Proc proc{"chrome.exe", 1044, Proc::Status::Running, "the_user", 25784320, Proc::Platform::x86};

        std::stringstream result;
        print_processes(result, {proc});

        ASSERT_EQ(result.str(), "chrome.exe               1044      Running   the_user            25180    32-bit\n");
    }

    TEST(PrintProcessesTest, GivenMultipleProcessesShouldCorrectlySortAndPrint) {
        std::stringstream result;
        print_processes(result, {{"firefox.exe", 1042, Proc::Status::Suspended, "SYSTEM", 25784320, Proc::Platform::x86_64},
                                {"chrome.exe", 1044, Proc::Status::Running, "the_user", 25784320, Proc::Platform::x86}});

        ASSERT_EQ(result.str(), "chrome.exe               1044      Running   the_user            25180    32-bit\n"
                                "firefox.exe              1042      Suspended SYSTEM              25180    64-bit\n");
    }
}