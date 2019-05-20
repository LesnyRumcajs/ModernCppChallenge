#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/algorithms_data_structs/shortest_path.h"

namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::Graph;

    TEST(GraphTest, EmptyGraphShouldHaveZeroSize) {
        auto graph = Graph{};
        ASSERT_EQ(graph.vertex_count(), 0);
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
}
