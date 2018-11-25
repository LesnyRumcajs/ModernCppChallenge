#pragma once

#include <string>
#include <iterator>
#include <sstream>
#include <algorithm>

namespace cppchallenge::string {
    /**
     * Helper for checking container iterator type
     */
    template<typename Container>
    using IteratorCategoryOf =
            typename std::iterator_traits<typename Container::iterator>::iterator_category;

    /**
     * Helper checking whether the iterator has random access iterator type
     */
    template<typename Container>
    using HaveRandomAccessIterator =
            std::is_base_of<std::random_access_iterator_tag, IteratorCategoryOf<Container>>;

    /**
     * Joins elements of a container (with random access iterator e.g. std::vector) with a given separator
     * @tparam Container
     * @param container
     * @param separator
     * @return
     */
    template<typename Container,
            typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type * = nullptr>
    std::string join(const Container& container, const char* separator = " ") {
        if (container.empty()) return std::string{};

        std::ostringstream oss;
        std::copy(container.begin(), container.end() - 1, std::ostream_iterator<std::string>(oss, separator));
        oss << *(container.end() - 1);

        return oss.str();
    }

    /**
     * Joins elements of a container (without random access iterator e.g. std::list) with a given separator
     * @tparam Container
     * @param container
     * @param separator
     * @return
     */
    template<typename Container,
            typename std::enable_if<!HaveRandomAccessIterator<Container>::value>::type * = nullptr>
    std::string join(const Container& container, const char* separator = " ") {
        if (container.empty()) return std::string{};

        std::ostringstream oss;

        oss << container.front();
        std::for_each(std::next(container.begin()), container.end(), [&oss, &separator](const auto& el) {
            oss << separator << el;
        });

        return oss.str();
    }
}
