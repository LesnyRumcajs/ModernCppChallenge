#include "logger.h"

#include <boost/filesystem.hpp>

namespace cppchallenge::stream_fs {
    Logger::Logger() {
        auto path = (boost::filesystem::temp_directory_path() / boost::filesystem::unique_path()).native();

        this->temp_file_path = path;
        this->temp_file.open(path);
    }

    Logger::~Logger() {
        if (this->temp_file.is_open()) {
            this->temp_file.close();
        }

        if (!this->temp_file_path.empty()) {
            std::filesystem::remove(this->temp_file_path);
        }
    }

    void Logger::save(const std::filesystem::path &path) {
        this->temp_file.close();
        std::filesystem::rename(this->temp_file_path, path);
        this->temp_file_path.clear();
    }

    Logger& Logger::operator<<(std::string_view text) {
        if (this->temp_file_path.empty()) {
            throw std::runtime_error("Unable to write to temporary file anymore.");
        }
        this->temp_file << text << std::endl;
        return *this;
    }

    const std::filesystem::path &Logger::get_temp_file_path() const {
        return temp_file_path;
    }
}