#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <list>

#include "../../src/lang/value_adder.h"

namespace {
    using namespace testing;
    using namespace cppchallenge::lang;

    TEST(PushValuesTest, GivenNoElementsShouldPreserve) {
        std::vector<int> v{1, 2, 3};
        push_values(v);

        ASSERT_THAT(v, ElementsAre(1, 2, 3));
    }

    TEST(PushValuesTest, GivenElementsShouldWorkOnVector) {
        std::vector<int> vector;
        push_values(vector, 1, 2, 3);
        ASSERT_THAT(vector, ElementsAre(1, 2, 3));
    }

    TEST(PushValuesTest, GivenElementsShouldWorkOnList) {
        std::list<int> list;
        push_values(list, 1, 2, 3);
        ASSERT_THAT(list, ElementsAre(1, 2, 3));
    }

    TEST(PushValuesTest, GivenElementsShouldWorkOnString) {
        std::string str;
        push_values(str, 'a', 'b', 'c');
        ASSERT_THAT(str, ElementsAre('a', 'b', 'c'));
    }
}