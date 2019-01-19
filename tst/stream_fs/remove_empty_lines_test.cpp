#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/stream_fs/remove_empty_lines.h"
#include "filesystem_helpers.h"

namespace {
    using namespace cppchallenge::stream_fs;
    using namespace testing;


    TEST(RemoveEmptyLinesTest, GivenEmptyFileShouldThrow) {
        ASSERT_THROW(remove_empty_lines("non_existent_file"), std::runtime_error);
    }

    TEST(RemoveEmptyLinesTest, GivenNoEmptyLinesShouldNotModify) {
        std::string content = "test\ntest2\n1234\n";
        auto temp_file = cppchallenge::stream_fs::test_helpers::TempFile(content);

        remove_empty_lines(temp_file.get_path());

        ASSERT_EQ(content, temp_file.get_file_content());
    }

    TEST(RemoveEmptyLinesTest, GivenEmptyLinesShouldRemove) {
        std::string content = "test\n\n\t\t   \n\t  1234\n";
        auto temp_file = cppchallenge::stream_fs::test_helpers::TempFile(content);

        remove_empty_lines(temp_file.get_path());

        ASSERT_EQ("test\n\t  1234\n", temp_file.get_file_content());
    }

    TEST(RemoveEmptyLinesTest, GivenAllLinesEmptyShouldCreateEmptyFile) {
        std::string content = "\n\n\n\t\t   \n\n";
        auto temp_file = cppchallenge::stream_fs::test_helpers::TempFile(content);

        remove_empty_lines(temp_file.get_path());

        ASSERT_THAT(temp_file.get_file_content(), IsEmpty());
    }
}