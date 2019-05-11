#pragma once

namespace cppchallenge::algorithms_data_structs {
    /**
     * Creates a range from the given input container using a projection function f
     */
    template <typename InElement, typename Allocator, typename F,
              typename OutElement = typename std::decay<typename std::result_of<
                    typename std::decay<F>::type&(typename std::vector<InElement,Allocator>::const_reference)
              >::type>::type>
    auto select(const std::vector<InElement, Allocator>& input, F&& f) {
        std::vector<OutElement> result;
        std::transform(input.begin(), input.end(), std::back_inserter(result), std::forward<F>(f));

        return result;
    }
}
