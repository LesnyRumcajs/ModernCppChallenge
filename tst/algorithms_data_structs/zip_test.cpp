#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/algorithms_data_structs/zip.h"

namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::zip;

    TEST(ZipTest, NoDataShouldReturnEmpty) {
        auto result = zip(std::vector<int>{}, std::vector<std::string>{});
        ASSERT_THAT(result, IsEmpty());
    }

    TEST(ZipTest, EvenDataShouldZip) {
        using namespace std::string_literals;
        auto result = zip(std::vector{1,2,3}, std::vector{"a"s, "b"s, "c"s});
        ASSERT_THAT(result, ElementsAre(Pair(1, "a"s), Pair(2, "b"s), Pair(3, "c"s)));
    }

    TEST(ZipTest, OddShouldDiscardUnused) {
        using namespace std::string_literals;
        auto result = zip(std::vector{1,2,3,4,5}, std::vector{"a"s, "b"s, "c"s});
        ASSERT_THAT(result, ElementsAre(Pair(1, "a"s), Pair(2, "b"s), Pair(3, "c"s)));
    }
}
