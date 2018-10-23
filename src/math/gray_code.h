#pragma once

#include <string>

namespace cppchallenge::math {
    std::string dec2binary(uint8_t number);

    std::string dec2gray(uint8_t number);

    uint8_t gray2dec(std::string gray);
}