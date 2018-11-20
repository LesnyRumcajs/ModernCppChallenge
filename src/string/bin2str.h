#pragma once

#include <string>
#include <ostream>
#include <algorithm>
#include <iomanip>

namespace cppchallenge::string {
    /**
     * Converts container of raw bytes to a hex-encoded string
     * @tparam Container
     * @param container
     * @param to_upcase true if the output should be uppercase
     * @return hex-encoded string
     */
    template <typename Container>
    std::string bin2str(const Container& container, const bool to_upcase = false) {
        std::ostringstream oss;
        oss << (to_upcase ? std::uppercase : std::nouppercase) << std::setfill('0') << std::hex;

        std::for_each(container.begin(), container.end(), [&oss](const auto el) {
            oss << std::setw(2) << static_cast<int>(el);
        });

        return oss.str();
    }
}
