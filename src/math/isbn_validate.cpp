#include <vector>
#include <algorithm>
#include <numeric>
#include "isbn_validate.h"

bool cppchallenge::math::is_valid_isbn_10(const std::string &isbn) {
    if (isbn.size() != 10 || std::any_of(isbn.begin(), isbn.end(), [](auto el) {
        return !std::isdigit(el);
    })) {
        return false;
    }

    std::vector<int> digits;
    std::transform(isbn.begin(), isbn.end(), std::back_inserter(digits), [](auto el) {
        return el - '1';
    });

    auto checksum = std::accumulate(digits.begin(), digits.end() - 1, 0, [idx = 1](auto sum, auto el) mutable {
        return sum + el * idx++;
    });

    return checksum % 11 == (digits.back());
}
