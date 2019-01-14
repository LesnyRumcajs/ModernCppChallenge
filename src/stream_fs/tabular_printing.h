#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>

namespace cppchallenge::stream_fs {
    struct Proc {
        enum class Status {
            Running,
            Suspended
        };

        /**
         * Returns string representation of process status
         * @param status
         * @return
         */
        static std::string status_to_text(const Status status) {
            return status == Status::Running ? "Running" : "Suspended";
        }

        enum class Platform {
            x86,
            x86_64
        };

        /**
         * Returns string representation process platform
         * @param platform
         * @return
         */
        static std::string platform_to_text(const Platform platform) {
            return platform == Platform::x86 ? "32-bit" : "64-bit";
        }

        std::string name;
        uint32_t id;
        Status status;
        std::string account;
        uint32_t  mem_size;
        Platform platform;
    };

    /**
     * Prints formatted processes to the given ostream
     * @param out
     * @param proc_list
     */
    void print_processes(std::ostream& out, std::vector<Proc> proc_list);
}