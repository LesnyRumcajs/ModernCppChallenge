#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/design_patterns/observed_vector.h"

namespace {
    using namespace testing;
    using namespace cppchallenge::design_patterns;

    TEST(ObservedVector, EmptyVector) {
        auto v = ObservedVector<std::string>();
        ASSERT_EQ(v.size(), 0);
    }

    TEST(ObservedVector, InitializedVector) {
        auto v = ObservedVector(5, 3);
        ASSERT_EQ(v.size(), 5);
    }

    TEST(ObservedVector, MovedVector) {
        auto v1 = ObservedVector(5,2);
        auto v2 = ObservedVector(std::move(v1));

        ASSERT_EQ(v2.size(), 5);
    }
    TEST(ObservedVector, CreateFromContainer) {
        auto v1 = std::vector{1,2,3};
        auto v2 = ObservedVector<int>(v1.begin(), v1.end());

        ASSERT_EQ(v2.size(), 3);
    }

    TEST(ObservedVector, CreateFromInitializerList) {
        ObservedVector v = {1,2,3};

        ASSERT_EQ(v.size(), 3);
    }

    TEST(ObservedVector, Assignment) {
        auto v = ObservedVector{1,2,3};
        auto v2 = v;

        ASSERT_EQ(v, v2);
    }

    TEST(ObservedVector, PushBack) {
        auto v = ObservedVector<int>();

        auto observer = std::make_shared<Observer>();
        v.add_observer(observer);

        ASSERT_THAT(observer->get_notifications(), IsEmpty());

        v.push_back(1);
        ASSERT_THAT(observer->get_notifications(), SizeIs(1));
        ASSERT_EQ(observer->get_notifications().back(), CollectionChangeNotification(CollectionAction::add, {0}));
        v.push_back(2);
        ASSERT_THAT(observer->get_notifications(), SizeIs(2));
        ASSERT_EQ(observer->get_notifications().back(), CollectionChangeNotification(CollectionAction::add, {1}));
    }

    TEST(ObservedVector, PopBack) {
        auto v = ObservedVector{1,2,3};

        auto observer = std::make_shared<Observer>();
        v.add_observer(observer);

        ASSERT_THAT(observer->get_notifications(), IsEmpty());
        v.pop_back();
        ASSERT_THAT(observer->get_notifications(), SizeIs(1));
        ASSERT_EQ(observer->get_notifications().back(), CollectionChangeNotification(CollectionAction::remove, {2}));
    }

    TEST(ObservedVector, Clear) {
        auto v = ObservedVector{1,2,3};

        auto observer = std::make_shared<Observer>();
        v.add_observer(observer);

        ASSERT_THAT(v, SizeIs(3));
        ASSERT_THAT(observer->get_notifications(), IsEmpty());
        v.clear();

        ASSERT_THAT(v, IsEmpty());
        ASSERT_THAT(observer->get_notifications(), SizeIs(1));
        ASSERT_EQ(observer->get_notifications().back(), CollectionChangeNotification(CollectionAction::clear));
    }

    TEST(ObservedVector, ObserversCanBeAddedAnytime) {
        auto v = ObservedVector{1,2,3};
        v.pop_back();

        auto observer = std::make_shared<Observer>();
        v.add_observer(observer);

        ASSERT_THAT(observer->get_notifications(), IsEmpty());
        v.pop_back();
        ASSERT_THAT(observer->get_notifications(), SizeIs(1));

        auto observer2 = std::make_shared<Observer>();
        v.add_observer(observer2);
        ASSERT_THAT(observer2->get_notifications(), IsEmpty());

        v.pop_back();

        ASSERT_THAT(observer->get_notifications(), SizeIs(2));
        ASSERT_THAT(observer2->get_notifications(), SizeIs(1));
    }

    TEST(ObservedVector, DuplicateObserversShouldNotifyOnce) {
        auto v = ObservedVector{1,2,3};

        auto observer = std::make_shared<Observer>();
        v.add_observer(observer);
        v.add_observer(observer);

        ASSERT_THAT(observer->get_notifications(), IsEmpty());
        v.pop_back();
        ASSERT_THAT(observer->get_notifications(), SizeIs(1));
    }

    TEST(ObservedVector, DeleteObservers) {
        auto v = ObservedVector{1,2,3};
        v.pop_back();

        auto observer = std::make_shared<Observer>();
        v.add_observer(observer);

        ASSERT_THAT(observer->get_notifications(), IsEmpty());
        v.pop_back();
        ASSERT_THAT(observer->get_notifications(), SizeIs(1));

        v.remove_observer(observer);

        v.pop_back();

        ASSERT_THAT(observer->get_notifications(), SizeIs(1));
    }

    TEST(ObservedVector, EqualityDoesNotIncludeObservers) {
        auto v1 = ObservedVector{1,2,3};

        auto observer = std::make_shared<Observer>();
        v1.add_observer(observer);

        auto v2 = ObservedVector{1,2,3};

        ASSERT_EQ(v1, v2);
    }

    TEST(ObservedVector, ExpiredObserversShouldNotThrow) {
        auto v = ObservedVector{1,2,3};
        {
            auto observer = std::make_shared<Observer>();
            v.add_observer(observer);
        }

        ASSERT_NO_THROW(v.pop_back());
        ASSERT_NO_THROW(v.push_back(3));

        ASSERT_THAT(v, SizeIs(3));
    }

}