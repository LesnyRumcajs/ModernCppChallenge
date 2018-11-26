#pragma once

#include <string>
#include <vector>

#include <boost/tokenizer.hpp>

namespace cppchallenge::string {

    template <class Elem>
    using tstring = std::basic_string<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

    /**
     * Splits string on the given delimiters
     * @tparam Elem
     * @param text
     * @param delimiters
     * @return tokens
     */
    template <typename Elem>
    std::vector<tstring<Elem>> tokenize(const tstring<Elem>& text, const tstring<Elem>& delimiters) {
        boost::char_separator<char> sep{delimiters.data()};
        boost::tokenizer<boost::char_separator<Elem>> tok{text, sep};

        return {tok.begin(), tok.end()};
    }
}
