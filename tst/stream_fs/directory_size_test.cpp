#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/stream_fs/directory_size.h"
#include "filesystem_helpers.h"

namespace {
    using namespace testing;

    class DirectorySizeTest : public ::testing::Test {
    protected:
        static constexpr char TEST_DIR_PATH[]{"tmp_dir_size_test"};
        void SetUp() override {
            std::filesystem::remove_all(TEST_DIR_PATH);
        }

        void TearDown() override {
            std::filesystem::remove_all(TEST_DIR_PATH);
        }
    };

    TEST_F(DirectorySizeTest, GivenInvalidPathShouldThrow) {
        ASSERT_THROW(cppchallenge::stream_fs::calculate_dir_size("non_existent_path"),
                     std::filesystem::filesystem_error);
    }

    TEST_F(DirectorySizeTest, GivenSingleFileAsAnArgumentShouldThrow) {
        cppchallenge::stream_fs::test_helpers::TempFile test_file("1234");
        ASSERT_THROW(cppchallenge::stream_fs::calculate_dir_size(test_file.get_path()),
                     std::filesystem::filesystem_error);
    }

    TEST_F(DirectorySizeTest, GivenDirectoryWithRegularFilesShouldSumSize) {
        auto path = std::filesystem::path(TEST_DIR_PATH) / "GivenDirectoryWithRegularFilesShouldSumSize";
        std::filesystem::create_directories(path);
        {
            std::ofstream of1(path / "test1");
            of1 << "1234";
            std::ofstream of2(path / "test2");
            of2 << "ab\n32";
        }

        ASSERT_EQ(cppchallenge::stream_fs::calculate_dir_size(path), 9);
    }

    TEST_F(DirectorySizeTest, GivenNestedDirectoryWithRegularFilesShouldSumSize) {
        auto path = std::filesystem::path(TEST_DIR_PATH) / "GivenNestedDirectoryWithRegularFilesShouldSumSize";
        std::filesystem::create_directories(path / "a" / "b");
        {
            std::ofstream of1(path / "a" / "test1");
            of1 << "1234";
            std::ofstream of2(path / "a" / "b" "test2");
            of2 << "ab\n32";
        }

        ASSERT_EQ(cppchallenge::stream_fs::calculate_dir_size(path), 9);
    }
}
