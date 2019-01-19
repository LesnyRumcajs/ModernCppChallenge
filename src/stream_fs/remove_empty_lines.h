#pragma once

#include <filesystem>
#include <fstream>
#include <boost/filesystem.hpp>

namespace cppchallenge::stream_fs {
    /**
     * Removes whitespace lines from a file
     * @param path
     */
    void remove_empty_lines(const std::filesystem::path& path) {
        auto temporary_path = (boost::filesystem::temp_directory_path() / boost::filesystem::unique_path()).native();
        {
            std::ifstream in(path);
            if (!in) {
                throw std::runtime_error("Unable to open file!");
            }


            std::ofstream out(temporary_path);
            if (!out) {
                throw std::runtime_error("Unable to create a temporary file!");
            }

            std::string line;
            while (std::getline(in, line)) {
                if (!line.empty() && line.find_first_not_of("\n\t ") != std::string::npos) {
                    out << line << '\n';
                }
            }
        }

        std::filesystem::remove(path);
        std::filesystem::rename(temporary_path, path);
    }
}