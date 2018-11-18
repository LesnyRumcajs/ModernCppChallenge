#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/lang/unique_handle.h"

namespace {
    class TestResourcePool {
    public:
        using HANDLE = int;
        static int acquire_resource() {
            HANDLE handle = 0;
            while(is_handle_in_use(++handle));
            handles.push_back(handle);
            return handle;
        }

        static void free_resource(int handle) {
            if (handle == 0) return;
            if (!is_handle_in_use(handle)) {
                throw std::invalid_argument("Resource not in use!");
            }

            handles.erase(std::remove(handles.begin(), handles.end(), handle));
        }

        static bool is_handle_in_use(HANDLE handle) {
            return handles.end() != std::find(handles.begin(), handles.end(), handle);
        }

        static HANDLE handles_count() {
            return static_cast<int>(handles.size());
        }

        static void reset_pool() {
            handles.clear();
        }

        static std::vector<TestResourcePool::HANDLE> handles;
    };

    std::vector<TestResourcePool::HANDLE> TestResourcePool::handles;


    struct TestResourceTraits {
        using ptr = TestResourcePool::HANDLE;
        static ptr invalid() noexcept {
            return 0;
        }

        static void close(ptr value) noexcept {
            TestResourcePool::free_resource(value);
        }
    };
    using TestResourceHandle = cppchallenge::lang::unique_handle<TestResourceTraits>;

    TEST(TestResourcePoolTest, AcquiringAndResettingNewHandlesShouldWorkCorrectly) {
        auto handle1 = TestResourcePool::acquire_resource();
        ASSERT_TRUE(TestResourcePool::is_handle_in_use(handle1));

        auto handle2 = TestResourcePool::acquire_resource();
        ASSERT_TRUE(TestResourcePool::is_handle_in_use(handle2));

        auto handle3 = TestResourcePool::acquire_resource();
        ASSERT_TRUE(TestResourcePool::is_handle_in_use(handle3));

        ASSERT_EQ(TestResourcePool::handles_count(), 3);

        TestResourcePool::reset_pool();
        ASSERT_EQ(TestResourcePool::handles_count(), 0);
    }

    TEST(TestResourcePoolTest, RemovingUnusedHandleShouldThrow) {
        ASSERT_THROW(TestResourcePool::free_resource(-1), std::invalid_argument);
    }

    TEST(UniqueHandleTest, ShouldCorrectlyAcquireResourceAndFree) {
        TestResourcePool::reset_pool();
        TestResourceTraits::ptr test_ptr;
        {
            TestResourceHandle handle(TestResourcePool::acquire_resource());
            test_ptr = handle.get();
            ASSERT_TRUE(TestResourcePool::is_handle_in_use(test_ptr));
        }
        ASSERT_FALSE(TestResourcePool::is_handle_in_use(test_ptr));
    }

    TEST(UniqueHandleTest, ShouldCorrectlyCompareHandles) {
        TestResourcePool::reset_pool();
        TestResourceHandle first_handle(TestResourcePool::acquire_resource());
        TestResourceHandle second_handle(TestResourcePool::acquire_resource());

        ASSERT_TRUE(first_handle != second_handle);

        TestResourceHandle& ref_first = first_handle;
        ASSERT_TRUE(first_handle == ref_first);
    }

    TEST(UniqueHandleTest, ShouldCorrectlySwapHandles) {
        TestResourcePool::reset_pool();
        TestResourceHandle first_handle(TestResourcePool::acquire_resource());
        auto first_ptr = first_handle.get();

        TestResourceHandle second_handle(TestResourcePool::acquire_resource());
        auto second_ptr = second_handle.get();

        swap(first_handle, second_handle);
        ASSERT_TRUE(first_handle.get() == second_ptr);
        ASSERT_TRUE(second_handle.get() == first_ptr);
    }

    TEST(UniqueHandleTest, ShouldCorrectlyResetOnDemand) {
        TestResourcePool::reset_pool();
        TestResourceHandle handle(TestResourcePool::acquire_resource());
        ASSERT_TRUE(TestResourcePool::is_handle_in_use(handle.get()));
        ASSERT_EQ(TestResourcePool::handles_count(), 1);
        handle.reset();
        ASSERT_EQ(TestResourcePool::handles_count(), 0);
    }

    TEST(UniqueHandleTest, ShouldCorrectlyReleaseOnDemand) {
        TestResourcePool::reset_pool();
        {
            TestResourceHandle handle(TestResourcePool::acquire_resource());
            ASSERT_TRUE(TestResourcePool::is_handle_in_use(handle.get()));
            ASSERT_EQ(TestResourcePool::handles_count(), 1);
            handle.release();
        }
        ASSERT_EQ(TestResourcePool::handles_count(), 1);
    }
};
