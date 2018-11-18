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

    using invalid_handle = cppchallenge::lang::unique_handle<TestResourceTraits>;
    TEST(UniqueHandleTest, ShouldCorrectlyAcquireResourceAndFree) {
        TestResourceTraits::ptr test_ptr;
        {
            invalid_handle handle(TestResourcePool::acquire_resource());
            test_ptr = handle.get();
            ASSERT_TRUE(TestResourcePool::is_handle_in_use(test_ptr));
        }
        ASSERT_FALSE(TestResourcePool::is_handle_in_use(test_ptr));
    }
};
