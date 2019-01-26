#pragma once

#include <filesystem>
#include <regex>

namespace cppchallenge::stream_fs {
    /**
     * Finds files based on a regex filename
     * @param path to directory containing files
     * @param regex for files
     * @return vector of directory entries matching the regex
     */
    std::vector<std::filesystem::directory_entry> regex_find(const std::filesystem::path& path, const std::regex re) {
        std::vector<std::filesystem::directory_entry> results;
        for(auto& p: std::filesystem::recursive_directory_iterator(path)) {
            if (!std::filesystem::is_directory(p) && std::regex_match(p.path().filename().c_str(), re)) {
                results.emplace_back(p);
            }
        }

        return results;
    }
}
