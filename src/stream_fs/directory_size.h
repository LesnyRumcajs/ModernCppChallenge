#pragma once

#include <filesystem>
#include <numeric>

namespace cppchallenge::stream_fs {
    /**
     * Recursively calculates the directory size
     * @param path
     * @return
     */
    std::uintmax_t calculate_dir_size(const std::filesystem::path& path) {
        auto it = std::filesystem::recursive_directory_iterator(path);
        return std::accumulate(std::filesystem::begin(it), std::filesystem::end(it), std::numeric_limits<std::uintmax_t>::min(), [](auto sum, const auto& file) {
            return sum + (std::filesystem::is_regular_file(file) ? std::filesystem::file_size(file) : 0);
        });
    }
}