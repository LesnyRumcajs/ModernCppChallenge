#pragma once

#include <string>
#include <string_view>

namespace cppchallenge::string {

    /**
     * Looks for a palindrome inside a string_view, either even or odd one. O(n^2) complexity.
     * @param text
     * @param result_begin
     * @param result_end
     * @param even
     */
    void palindrome_search(const std::string_view &text, std::string_view::const_iterator &result_begin,
                           std::string_view::const_iterator &result_end, bool even) {
        for (auto it = std::next(text.begin()); it != text.end(); ++it) {
            auto palindrome_start = it - 1;
            auto palindrome_end = even ? it : it + 1;

            while (palindrome_start >= text.begin() && palindrome_end < text.end() &&
                   *palindrome_start == *palindrome_end) {
                if (std::distance(palindrome_start, palindrome_end) > std::distance(result_begin, result_end)) {
                    result_begin = palindrome_start;
                    result_end = palindrome_end;
                }

                palindrome_start = std::prev(palindrome_start);
                palindrome_end = std::next(palindrome_end);
            }
        }
    }

    /**
     * Looks for an even-length palindrome.
     * @param text
     * @param result_begin
     * @param result_end
     */
    void
    even_length_palindrome_search(const std::string_view &text, std::string_view::const_iterator &result_begin,
                                  std::string_view::const_iterator &result_end) {
        palindrome_search(text, result_begin, result_end, true);
    }

    /**
     * Looks for an odd-length palindrome.
     * @param text
     * @param result_begin
     * @param result_end
     */
    void
    odd_length_palindrome_search(const std::string_view &text, std::string_view::const_iterator &result_begin,
                                 std::string_view::const_iterator &result_end) {
        palindrome_search(text, result_begin, result_end, false);
    }

    /**
     * Finds the longest palindrome in a given std::string_view.
     * @param text
     * @return longest palindrome
     */
    std::string longest_palindrome(const std::string_view text) {
        if (text.empty()) {
            return "";
        }

        std::string_view::const_iterator result_begin = text.begin();
        std::string_view::const_iterator result_end = text.begin();

        odd_length_palindrome_search(text, result_begin, result_end);
        even_length_palindrome_search(text, result_begin, result_end);

        return {result_begin, result_end + 1};
    }
}
