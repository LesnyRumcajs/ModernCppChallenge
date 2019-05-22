#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/algorithms_data_structs/shortest_path.h"

namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::Graph;
    using cppchallenge::algorithms_data_structs::shortest_path;

    TEST(GraphTest, EmptyGraphShouldHaveZeroSize) {
        auto graph = Graph{};
        ASSERT_EQ(graph.vertex_count(), 0);
        ASSERT_TRUE(graph.empty());
    }

    TEST(GraphTest, VertexExist) {
        auto graph = Graph{};
        graph.add_edge(1,2, 0.1);

        ASSERT_TRUE(graph.vertex_exist(1));
        ASSERT_TRUE(graph.vertex_exist(2));
        ASSERT_FALSE(graph.vertex_exist(3));
    }

    TEST(GraphTest, SingleEdgeUnidirectional) {
        auto graph = Graph{};
        graph.add_edge(1,2, 0.1, false);

        ASSERT_EQ(graph.vertex_count(), 1);
        ASSERT_THAT(graph.get_verteces(), ElementsAre(1));
    }

    TEST(GraphTest, SingleEdgeBidirectional) {
        auto graph = Graph{};
        graph.add_edge(1,2, 0.1);

        ASSERT_EQ(graph.vertex_count(), 2);
        ASSERT_THAT(graph.get_verteces(), ElementsAre(1,2));
    }

    TEST(GraphTest, MultipleEdge) {
        auto graph = Graph{};
        graph.add_edge(1,2, 0.1);
        graph.add_edge(1,3, 0.2);
        graph.add_edge(3,2, 0.2);

        ASSERT_EQ(graph.vertex_count(), 3);
        ASSERT_THAT(graph.get_verteces(), ElementsAre(1,2,3));
        ASSERT_THAT(graph.get_neighbors(1), ElementsAre(Pair(2, 0.1), Pair(3, 0.2)));
    }

    TEST(GraphTest, InfinityLargerThanMax) {
        ASSERT_GT(Graph<>::infinity, std::numeric_limits<typename Graph<>::weight_type>::max());
    }

    TEST(ShortestPathTest, EmptyGraphShouldThrow) {
        auto graph = Graph{};
        int src{1};
        auto distances = std::map<int, double>{};
        auto previous = std::map<int, int>{};

        ASSERT_THROW(shortest_path(graph, src, distances, previous), std::invalid_argument);
    }

    TEST(ShortestPathTest, SourceNotInGraphShouldThrow) {
        auto graph = Graph{};
        graph.add_edge(1,2,0.1);

        int src{3};
        auto distances = std::map<int, double>{};
        auto previous = std::map<int, int>{};

        ASSERT_THROW(shortest_path(graph, src, distances, previous), std::invalid_argument);
    }

    TEST(ShortestPathTest, ShouldCalculateShortestPath) {
        auto graph = Graph<char, double>{};
        graph.add_edge('A', 'B', 7);
        graph.add_edge('A', 'C', 9);
        graph.add_edge('A', 'F', 14);
        graph.add_edge('B', 'C', 10);
        graph.add_edge('B', 'D', 15);
        graph.add_edge('C', 'D', 11);
        graph.add_edge('C', 'F', 2);
        graph.add_edge('D', 'E', 6);
        graph.add_edge('E', 'F', 9);

        const auto src = 'A';
        auto distances = std::map<char, double>{};
        auto previous = std::map<char, char>{};

        shortest_path(graph, src, distances, previous);

        ASSERT_EQ(distances['B'], 7);
        ASSERT_EQ(distances['C'], 9);
        ASSERT_EQ(distances['D'], 20);
        ASSERT_EQ(distances['E'], 20);
        ASSERT_EQ(distances['F'], 11);

        ASSERT_EQ(previous['B'], 'A');
        ASSERT_EQ(previous['C'], 'A');
        ASSERT_EQ(previous['D'], 'C');
        ASSERT_EQ(previous['E'], 'F');
        ASSERT_EQ(previous['F'], 'C');
    }

}
