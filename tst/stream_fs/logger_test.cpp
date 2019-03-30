#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/stream_fs/logger.h"
#include "filesystem_helpers.h"

namespace {
    using namespace testing;

    TEST(LoggerTest, ShouldCreateTemporaryFileAndDeleteIt) {
        std::filesystem::path logger_file;
        {
            cppchallenge::stream_fs::Logger logger;
            logger_file = logger.temp_file_path;
            ASSERT_TRUE(std::filesystem::exists(logger_file));
        }

        ASSERT_FALSE(std::filesystem::exists(logger_file));
    }

    TEST(LoggerTest, ShouldWriteToTemporaryFile) {
       cppchallenge::stream_fs::Logger logger;
       logger << "test" << "test2";

       std::ifstream ifs(logger.temp_file_path);

       std::string temp_file_data((std::istreambuf_iterator<char>(ifs)),
                        std::istreambuf_iterator<char>());

       ASSERT_EQ(temp_file_data, "test\ntest2\n");
    }

    TEST(LoggerTest, ShouldCreatePermanentFile) {
        cppchallenge::stream_fs::Logger logger;
        logger << "test" << "test2";

        auto path = (boost::filesystem::temp_directory_path() / boost::filesystem::unique_path()).native();
        logger.save(path);

        std::ifstream ifs(path);
        std::string persistent_file_data((std::istreambuf_iterator<char>(ifs)),
                                   std::istreambuf_iterator<char>());

        ASSERT_EQ(persistent_file_data, "test\ntest2\n");

    }

    TEST(LoggerTest, ShouldThrowWhenWriteAfterSave) {
        cppchallenge::stream_fs::Logger logger;
        logger << "test" << "test2";

        auto path = (boost::filesystem::temp_directory_path() / boost::filesystem::unique_path()).native();
        logger.save(path);
        ASSERT_THROW(logger << "killme", std::runtime_error);
    }
}
