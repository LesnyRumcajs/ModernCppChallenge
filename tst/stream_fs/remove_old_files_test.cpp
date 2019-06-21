#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <chrono>

#include "../../src/stream_fs/remove_old_files.h"
#include "filesystem_helpers.h"

namespace {
    using namespace testing;
    using namespace std::chrono_literals;
    using namespace cppchallenge::stream_fs;
    using namespace cppchallenge::stream_fs::test_helpers;

    class IsOlderThanTest : public ::testing::Test {
    protected:
        static constexpr char TEST_DIR_PATH[]{"tmp_is_older_than_test"};

        void SetUp() override {
            std::filesystem::remove_all(TEST_DIR_PATH);
        }

        void TearDown() override {
            std::filesystem::remove_all(TEST_DIR_PATH);
        }
    };

    TEST_F(IsOlderThanTest, GivenNonExistentFileShouldThrow) {
        ASSERT_THROW(is_older_than(std::filesystem::path{TEST_DIR_PATH} / "nope", 1h),
                     std::filesystem::filesystem_error);
    }

    TEST_F(IsOlderThanTest, GivenOlderFileShouldReturnTrue) {
        auto tmp_file = TempFile("");

        std::filesystem::last_write_time(tmp_file.get_path(),  std::filesystem::file_time_type::clock::now()- 5min);
        ASSERT_TRUE(is_older_than(tmp_file.get_path(), 1min));
    }

    TEST_F(IsOlderThanTest, GivenYoungerFileShouldReturnFalse) {
        auto tmp_file = TempFile("");

        std::filesystem::last_write_time(tmp_file.get_path(), std::filesystem::file_time_type::clock::now() - 5min);
        ASSERT_FALSE(is_older_than(tmp_file.get_path(), 10min));
    }

    class RemoveOldFilesTest : public ::testing::Test {
    protected:
        static constexpr char TEST_DIR_PATH[]{"tmp_remove_old_files_test"};

        void SetUp() override {
            std::filesystem::remove_all(TEST_DIR_PATH);
        }

        void TearDown() override {
            std::filesystem::remove_all(TEST_DIR_PATH);
        }
    };

    TEST_F(RemoveOldFilesTest, GivenEmptyDirShouldReturnZero) {
        ASSERT_EQ(remove_old_files(std::filesystem::path(TEST_DIR_PATH), 1h), 0);
    }

    TEST_F(RemoveOldFilesTest, GivenOnlyOlderFilesShouldDeleteAll) {
        auto path = std::filesystem::path(TEST_DIR_PATH) / "GivenOnlyOlderFilesShouldDeleteAll";
        std::filesystem::create_directories(path);
        {
            std::ofstream of1(path / "test1");
            std::ofstream of2(path / "test2");
        }

        std::filesystem::last_write_time(path / "test1", std::filesystem::file_time_type::clock::now() - 5min);
        std::filesystem::last_write_time(path / "test2", std::filesystem::file_time_type::clock::now() - 15min);

        ASSERT_EQ(remove_old_files(path, 1min), 2);
        ASSERT_FALSE(std::filesystem::exists(path / "test1"));
        ASSERT_FALSE(std::filesystem::exists(path / "test2"));
    }

    TEST_F(RemoveOldFilesTest, GivenOnlyYoungerFilesShouldDeleteNone) {
        auto path = std::filesystem::path(TEST_DIR_PATH) / "GivenOnlyYoungerFilesShouldDeleteNone";
        std::filesystem::create_directories(path);
        {
            std::ofstream of1(path / "test1");
            std::ofstream of2(path / "test2");
        }

        std::filesystem::last_write_time(path / "test1", std::filesystem::file_time_type::clock::now() + 5min);
        std::filesystem::last_write_time(path / "test2", std::filesystem::file_time_type::clock::now() + 15min);

        ASSERT_EQ(remove_old_files(path, 1min), 0);
        ASSERT_TRUE(std::filesystem::exists(path / "test1"));
        ASSERT_TRUE(std::filesystem::exists(path / "test2"));
    }

    TEST_F(RemoveOldFilesTest, GivenMixedFilesShouldCorrectlyDeleteRecursive) {
        auto path = std::filesystem::path(TEST_DIR_PATH) / "GivenMixedFilesShouldCorrectlyDeleteRecursive";
        std::filesystem::create_directories(path);
        {
            std::ofstream of1(path / "test1");
            std::ofstream of2(path / "test2");
            std::filesystem::create_directories(path / "test_dir");
            std::ofstream of3(path / "test_dir" / "test3");
            std::ofstream of4(path / "test_dir" / "test4");
        }

        std::filesystem::last_write_time(path / "test1", std::filesystem::file_time_type::clock::now() + 1h + 5min);
        std::filesystem::last_write_time(path / "test2", std::filesystem::file_time_type::clock::now() - 50s);
        std::filesystem::last_write_time(path / "test_dir" / "test3", std::filesystem::file_time_type::clock::now() + 50h);
        std::filesystem::last_write_time(path / "test_dir" / "test4", std::filesystem::file_time_type::clock::now() - 10min);

        ASSERT_EQ(remove_old_files(path, 0ms), 2);
        ASSERT_TRUE(std::filesystem::exists(path / "test1"));
        ASSERT_FALSE(std::filesystem::exists(path / "test2"));
        ASSERT_TRUE(std::filesystem::exists(path / "test_dir" / "test3"));
        ASSERT_FALSE(std::filesystem::exists(path / "test_dir" / "test4"));
    }
}