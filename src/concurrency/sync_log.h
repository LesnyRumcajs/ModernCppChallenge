#pragma once

#include <mutex>
#include <ostream>
#include <iostream>

namespace cppchallenge::concurrency {
    /**
     * Synchronised logging class
     */
    class SyncLogger {
    public:
        explicit SyncLogger(std::ostream& os = std::cout) : os(os) {}

        void log(std::string_view data) {
            std::lock_guard lock(mut);
            os << data << '\n';
        }

    private:
        std::ostream& os;
        std::mutex mut;
    };
}
