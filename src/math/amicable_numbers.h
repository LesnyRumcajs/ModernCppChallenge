#pragma once

#include <vector>

namespace cppchallenge::math {
    using amicable_number = std::pair<unsigned, unsigned>;
    using amicable_numbers = std::vector<amicable_number>;

    amicable_numbers get_amicable_numbers(unsigned limit);
}