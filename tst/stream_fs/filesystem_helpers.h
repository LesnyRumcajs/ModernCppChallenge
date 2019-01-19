#pragma once

#include <boost/filesystem.hpp>
#include <fstream>
#include <filesystem>

namespace cppchallenge::stream_fs::test_helpers {
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
}