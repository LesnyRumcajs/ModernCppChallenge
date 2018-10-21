#include <numeric>
#include <algorithm>
#include "amicable_numbers.h"
#include "abundant_numbers.h"

cppchallenge::math::amicable_numbers cppchallenge::math::get_amicable_numbers(unsigned limit) {
    amicable_numbers result;

    for (unsigned number = 0; number <= limit; ++number) {
        auto number_divisors = cppchallenge::math::get_proper_divisors(number);
        auto candidate = std::accumulate(number_divisors.begin(), number_divisors.end(), 0u);

        auto candidate_divisors = cppchallenge::math::get_proper_divisors(candidate);
        auto candidate_sum_of_divisors = std::accumulate(candidate_divisors.begin(), candidate_divisors.end(), 0u);

        bool is_different = candidate != number;
        bool is_unique = std::find_if(result.begin(), result.end(), [candidate](auto el) {
            return el.first == candidate;
        }) == result.end();
        bool is_amicable = candidate_sum_of_divisors == number;

        if (is_different && is_unique && is_amicable) {
            result.emplace_back(std::make_pair(number, candidate));
        }
    }

    return result;
}
