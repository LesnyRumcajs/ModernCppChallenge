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

        auto empty() const {
            return data.empty();
        }

        auto vertex_exist(const Vertex vertex) const {
            return data.find(vertex) != data.end();
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

    /**
     * Shortest path using Dijkstra's algorithm
     */
    template<typename Vertex = int, typename Weight = double>
    void shortest_path(const Graph<Vertex, Weight>& graph, const Vertex src, std::map<Vertex, Weight>& distances, std::map<Vertex, Vertex>& previous){
        if (graph.empty() || !graph.vertex_exist(src)) {
            throw std::invalid_argument("Empty graph!");
        }

        previous.clear();
        distances.clear();

        for (const auto& vertex : graph.get_verteces()) {
            distances[vertex] = graph.infinity;
        }
        distances[src] = 0;

        std::set<typename Graph<Vertex, Weight>::neighbor_type> vertex_queue;
        vertex_queue.insert(std::make_pair(distances[src], src));

        while (!vertex_queue.empty()) {
            auto dist = vertex_queue.begin()->first;
            auto u = vertex_queue.begin()->second;

            vertex_queue.erase(vertex_queue.begin());

            const auto& neighbors = graph.get_neighbors(u);

            for (const auto& neighbor : neighbors) {
                auto vertex = neighbor.first;
                auto weight = neighbor.second;

                auto dist_via_u = dist + weight;

                if (dist_via_u < distances[vertex]) {
                    vertex_queue.erase(std::make_pair(distances[vertex], vertex));

                    distances[vertex] = dist_via_u;
                    previous[vertex] = u;
                    vertex_queue.insert(std::make_pair(distances[vertex], vertex));
                }
            }
        }
    }
}