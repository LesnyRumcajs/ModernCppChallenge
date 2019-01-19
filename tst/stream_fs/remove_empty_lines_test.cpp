#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/stream_fs/remove_empty_lines.h"

namespace {
    using namespace cppchallenge::stream_fs;
    using namespace testing;

    class TempFile {
    public:

        explicit TempFile(const std::string& content){
            auto path = (boost::filesystem::temp_directory_path() / boost::filesystem::unique_path()).native();
            std::ofstream of(path);
            of << content;
            file_path = path;
        }

        ~TempFile() {
            std::filesystem::remove(file_path);
        }

        const std::filesystem::path &get_path() const {
            return file_path;
        }

        std::string get_file_content() {
            std::ifstream is(file_path);
            std::string result((std::istreambuf_iterator<char>(is)),
                               std::istreambuf_iterator<char>());

            return result;
        }
    private:
        std::filesystem::path file_path;
    };


    TEST(RemoveEmptyLinesTest, GivenEmptyFileShouldThrow) {
        ASSERT_THROW(remove_empty_lines("non_existent_file"), std::runtime_error);
    }

    TEST(RemoveEmptyLinesTest, GivenNoEmptyLinesShouldNotModify) {
        std::string content = "test\ntest2\n1234\n";
        auto temp_file = TempFile(content);

        remove_empty_lines(temp_file.get_path());

        ASSERT_EQ(content, temp_file.get_file_content());
    }

    TEST(RemoveEmptyLinesTest, GivenEmptyLinesShouldRemove) {
        std::string content = "test\n\n\t\t   \n\t  1234\n";
        auto temp_file = TempFile(content);

        remove_empty_lines(temp_file.get_path());

        ASSERT_EQ("test\n\t  1234\n", temp_file.get_file_content());
    }

    TEST(RemoveEmptyLinesTest, GivenAllLinesEmptyShouldCreateEmptyFile) {
        std::string content = "\n\n\n\t\t   \n\n";
        auto temp_file = TempFile(content);

        remove_empty_lines(temp_file.get_path());

        ASSERT_THAT(temp_file.get_file_content(), IsEmpty());
    }
}