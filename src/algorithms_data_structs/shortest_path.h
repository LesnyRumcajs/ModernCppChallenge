#pragma once

#include <utility>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>

namespace cppchallenge::algorithms_data_structs {
    template <typename Vertex = int, typename Weight = double>
    class Graph {
    public:
        using vertex_type = Vertex;
        using weight_type = Weight;
        using neighbor_type = std::pair<Vertex, Weight>;
        using neighbor_list_type = std::vector<neighbor_type>;

        static constexpr auto infinity = std::numeric_limits<Weight>::infinity();

        void add_edge(const Vertex src, const Vertex dst, const Weight weight, const bool bidirectional = true) {
            data[src].emplace_back(std::make_pair(dst, weight));

            if (bidirectional) {
                data[dst].emplace_back(std::make_pair(src, weight));
            }
        }

        auto vertex_count() const {
            return data.size();
        }

        auto get_verteces() const {
            std::vector<Vertex> result;

            std::transform(data.begin(), data.end(), std::back_inserter(result), [](const auto& item) {
                return item.first;
            });

            return result;
        }

        const auto& get_neighbors(const Vertex& vertex) const {
            return data.at(vertex);
        }
    private:
        std::map<Vertex, neighbor_list_type> data;
    };
}