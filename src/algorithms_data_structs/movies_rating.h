#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

namespace cppchallenge::algorithms_data_structs {
    /**
     * Calculates truncated mean
     */
    template<typename Value>
    auto truncated_mean(std::vector<Value> values, const double truncate_percentage) {
        if (values.empty()) {
            return 0.0;
        }
        std::sort(values.begin(), values.end());

        auto to_remove = static_cast<typename std::vector<Value>::size_type>(std::ceil(values.size() * truncate_percentage));

        values.resize(values.size() - to_remove);
        values.erase(values.begin(), values.begin() + to_remove);

        auto sum = std::accumulate(values.begin(), values.end(), static_cast<Value>(0), [](const auto sum, const auto rating) {
           return sum + rating;
        });

        return static_cast<double>(sum) / values.size();
    }

    /**
     * Calculates average rating for movies
     */
    template<typename Id, typename Ratings>
    auto average_movies(const std::vector<std::pair<Id, Ratings>>& movies) {
        std::vector<std::pair<Id, double>> result;

        for (const auto& [id, ratings] : movies) {
            result.push_back({id, truncated_mean(ratings, 0.05)});
        }

        return result;
    }
}
