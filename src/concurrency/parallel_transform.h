#pragma once

#include <algorithm>
#include <execution>

namespace cppchallenge::concurrency {
    /**
     * Parallel transform of a container - it should be noted that parallel version of transform makes sense only with
     * large datasets, e.g. 200k (on my machine it was the threshold - less than 200k, the sequential transform was
     * faster).
     *
     * Another note is that it makes sense to use it only on random access containers, e.g. vectors, arrays. Using it on
     * e.g. lists is ALWAYS slower.
     * A specialized variation of this template function should be implemented for non-random access iterators.
     */
    template<typename T, typename F>
    T parallel_transform(const T &data, F &&f) {
        T out(data.size());
        std::transform(std::execution::par, data.begin(), data.end(), out.begin(), std::forward<F>(f));
        return out;
    }
}
