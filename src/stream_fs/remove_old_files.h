#pragma once

#include <filesystem>
#include <chrono>

namespace cppchallenge::stream_fs {
    /**
     * Verifies if given file is older than given time, e.x. 1h
     * @tparam Duration
     * @param path
     * @param duration
     * @return
     */
    template<typename Duration>
    bool is_older_than(const std::filesystem::path &path, const Duration duration) {
        auto last_write_time = std::filesystem::last_write_time(path).time_since_epoch();
        auto target_time = (std::filesystem::file_time_type::clock::now() - duration).time_since_epoch();

        return std::chrono::duration_cast<Duration>(target_time - last_write_time).count() > 0;
    }

    /**
     * Deletes files older than given time, e.x. 1h. Doesn't remove directories.
     * @tparam Duration
     * @param path
     * @param duration
     * @return removed files
     */
    template<typename Duration>
    size_t remove_old_files(const std::filesystem::path &path, const Duration duration) {
        if (!std::filesystem::exists(path)) {
            return 0;
        }

        auto files_removed_count = size_t(0);

        if (std::filesystem::is_directory(path)) {
            for (const auto &element : std::filesystem::directory_iterator(path)) {
                files_removed_count += remove_old_files(element, duration);
            }
        } else if (is_older_than(path, duration)) {
            files_removed_count += std::filesystem::remove(path);
        }

        return files_removed_count;
    }
}
