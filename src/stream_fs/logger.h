#pragma once

#include <filesystem>
#include <fstream>

namespace cppchallenge::stream_fs {
    class Logger {
    public:
        /**
         * @brief Creates logger object with an associated temporary log file.
         */
        Logger();

        /**
         * @brief Destroys the object and the associated temporary log file with it.
         */
        virtual ~Logger();

        /**
         * Saves the temporary log file to a permanent location.
         * @param path permanent log file location.
         */
        void save(const std::filesystem::path &path);

        /**
         * Appends data to temporary log file
         */
        Logger& operator<<(std::string_view text);

        /**
         * Temporary log file location
         */
        std::filesystem::path temp_file_path;
    private:
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;


        /**
         * Returns the path to the temporary file
         */
        const std::filesystem::path &get_temp_file_path() const;

        /**
         * Temporary log file handle
         */
        std::ofstream temp_file;
    };
}
