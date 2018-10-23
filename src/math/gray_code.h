#pragma once

#include <string>

namespace cppchallenge::math {
    /**
     * @param number
     * @return binary representation of a decimal
     */
    std::string dec2binary(uint8_t number);

    /**
     * @param number
     * @return gray representation of a decimal
     */
    std::string dec2gray(uint8_t number);

    /**
     * @param gray
     * @return decimal value of a grey representation
     */
    uint8_t gray2dec(std::string gray);
}