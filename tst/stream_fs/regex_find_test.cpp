#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include "../../src/stream_fs/regex_find.h"

namespace {
    using namespace testing;
    using namespace cppchallenge::stream_fs;

    class RegexFindTest : public ::testing::Test {
    protected:
        static constexpr char TEST_DIR_PATH[]{"tmp_regex_find"};

        void SetUp() override {
            std::filesystem::remove_all(TEST_DIR_PATH);
        }

        void TearDown() override {
            std::filesystem::remove_all(TEST_DIR_PATH);
        }
    };


    TEST_F(RegexFindTest, GivenEmptyDirectoryShouldReturnNothing) {
        std::filesystem::create_directories(TEST_DIR_PATH);
        ASSERT_THAT(regex_find(std::filesystem::path(TEST_DIR_PATH), std::regex(R"(\w+)")), IsEmpty());
    }

    TEST_F(RegexFindTest, GivenNonMatchingFilesShouldReturnNothing) {
        auto path = std::filesystem::path(TEST_DIR_PATH) / "GivenNonMatchingFilesShouldReturnNothing";
        std::filesystem::create_directories(path);
        {
            std::ofstream f1(path / "f1");
            std::ofstream f2(path / ".");
        }

        ASSERT_THAT(regex_find(std::filesystem::path(TEST_DIR_PATH), std::regex(R"(^\d+)")), IsEmpty());
    }

    TEST_F(RegexFindTest, GivenMatchingFilesShouldReturnThem) {
        auto path = std::filesystem::path(TEST_DIR_PATH) / "GivenMatchingFilesShouldReturnThem";
        std::filesystem::create_directories(path);
        {
            std::ofstream f1(path / "f1");
            std::ofstream f2(path / ".k");
        }

        auto result = regex_find(std::filesystem::path(TEST_DIR_PATH), std::regex(R"(^.{1,2}$)"));

        ASSERT_EQ(result.size(), 2);

        auto filenames = {result.at(0).path().filename(), result.at(1).path().filename()};
        ASSERT_THAT(filenames, UnorderedElementsAre("f1", ".k"));
    }

    TEST_F(RegexFindTest, GivenMixedFilesShouldReturnMatchesRecursive) {
        auto path = std::filesystem::path(TEST_DIR_PATH) / "GivenMixedFilesShouldReturnMatchesRecursive";
        std::filesystem::create_directories(path);
        {
            std::ofstream file1(path / "__file1");
            std::ofstream file2(path / ".file2");

            std::filesystem::create_directories(path / "deep");
            std::ofstream file3(path / "deep" / "test__");
            std::ofstream file4(path / "deep" / "__DROP table");
        }

        auto result = regex_find(std::filesystem::path(TEST_DIR_PATH), std::regex(R"(^__.+$)"));

        ASSERT_EQ(result.size(), 2);

        auto filenames = {result.at(0).path().filename(), result.at(1).path().filename()};
        ASSERT_THAT(filenames, UnorderedElementsAre("__file1", "__DROP table"));
    }
}