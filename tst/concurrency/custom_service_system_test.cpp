#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <future>

#include "../../src/concurrency/custom_service_system.h"

namespace {
    using namespace testing;
    using namespace cppchallenge::concurrency;
    using namespace std::chrono_literals;
    TEST(TicketMachineTest, ShouldGenerateSimple) {
        auto machine = TicketMachine();

        ASSERT_EQ(machine.count(), 0);
        ASSERT_EQ(machine.generate_ticket(), 1);
        ASSERT_EQ(machine.generate_ticket(), 2);
    }

    TEST(TicketMachineTest, ShouldGenerateMultiThreaded) {
        auto machine = TicketMachine();

        auto task1 = std::async(std::launch::async, [&machine]() {
            for (auto i{0u}; i < 10'000; ++i) {
                machine.generate_ticket();
            }
        });

        auto task2 = std::async(std::launch::async, [&machine]() {
            for (auto i{0u}; i < 10'000; ++i) {
                machine.generate_ticket();
            }
        });

        task1.wait(); task2.wait();

        ASSERT_EQ(machine.count(), 20'000);
    }

    TEST(CustomerTest, CustomersComparedBasedOnTheTicketNr) {
        auto customer1 = Customer(23);
        auto customer2 = Customer(33);
        ASSERT_EQ(customer1.get_ticket_number(), 23);
        ASSERT_EQ(customer2.get_ticket_number(), 33);

        ASSERT_FALSE(customer1 < customer2);
    }

    TEST(OfficeTest, OpenClose) {
        auto office = Office();
        ASSERT_FALSE(office.is_office_open());

        office.open(1);

        ASSERT_TRUE(office.is_office_open());

        office.close();

        ASSERT_FALSE(office.is_office_open());
    }

    TEST(OfficeTest, MultipleOpenShouldThrow) {
        auto office = Office();
        office.open(1);

        ASSERT_THROW(office.open(1), std::runtime_error);
    }

    TEST(OfficeTest, CloseWhenClosedShouldNotThrow) {
        auto office = Office();
        office.close();

        ASSERT_NO_THROW(office.close());
    }

    TEST(OfficeTest, QueueStaysWhenOfficeIsNotOpen) {
        auto office = Office();
        office.add_customer(5ms);
        office.add_customer(5ms);
        office.add_customer(5ms);

        ASSERT_EQ(office.queue_size(), 3);
    }

    TEST(OfficeTest, QueueClearsAfterOfficeOpens) {
        auto office = Office();
        office.add_customer(5ms);
        office.add_customer(5ms);
        office.add_customer(5ms);

        office.open(3);

        std::this_thread::sleep_for(100ms);

        ASSERT_EQ(office.queue_size(), 0);
    }
}
