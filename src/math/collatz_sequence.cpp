#include <stdexcept>
#include "collatz_sequence.h"

namespace cppchallenge::math {
    collatz_numbers create_collatz_sequence(collatz_number number) {
        if (number < 2) {
            throw std::invalid_argument("invalid number for collatz sequence");
        }

        std::vector<collatz_number> result;
        while (number > 1) {
            result.push_back(number);
            if (number % 2 == 0) {
                number /= 2;
            } else {
                number = number * 3 + 1;
            }
        }

        result.push_back(1);

        return result;
    }

    std::pair<collatz_number, collatz_number> longest_collatz_sequence(collatz_number limit) {
        if (limit < 2) {
            throw std::invalid_argument("invalid number for collatz sequence");
        }
        std::pair<collatz_number, collatz_number> result;

        std::vector<collatz_number> cache(limit + 1, 0);

        for (collatz_number candidate{2}; candidate <= limit; ++candidate) {
            collatz_number temp_number{candidate};
            collatz_number count{};

            while (temp_number != 1 && temp_number >= candidate) {
                ++count;
                temp_number = (temp_number % 2) ? temp_number * 3 + 1 : temp_number / 2;
            }

            cache[candidate] = count + cache[temp_number];

            if (cache[candidate] > result.first) {
                result.first = cache[candidate];
                result.second = candidate;
            }

        }

        return result;
    }
}
