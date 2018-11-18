#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/lang/unique_handle.h"

namespace {
    class TestResourcePool {
    public:
        using HANDLE = int;
        static int acquire_resource() {
            HANDLE handle = 1;
            while(is_handle_in_use(handle++));
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
