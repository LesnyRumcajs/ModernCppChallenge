#include <gtest/gtest.h>

#include "../../src/design_patterns/acceptance_system.h"

namespace {
    using namespace testing;
    using namespace cppchallenge::design_patterns;

    TEST(AcceptanceSystem, CanCreateAnEmployeeWithAnyRole) {
        ASSERT_NO_THROW(Employee("a", std::make_unique<RegularRole>()));
        ASSERT_NO_THROW(Employee("b", std::make_unique<PMRole>()));
        ASSERT_NO_THROW(Employee("c", std::make_unique<DirectorRole>()));
        ASSERT_NO_THROW(Employee("d", std::make_unique<CEORole>()));
    }

    TEST(AcceptanceSystem, SmallExpenseRegularShouldAccept) {
        auto regular = Employee("Grzesiu", std::make_unique<RegularRole>());
        auto expense = Expense("dinner", 20);
        ASSERT_EQ(regular.get_approver(expense), "Grzesiu");
    }

    TEST(AcceptanceSystem, MediumExpenseManagerShouldAccept) {
        auto regular = std::make_unique<Employee>("Grzesiu", std::make_unique<RegularRole>());
        auto pm = std::make_shared<Employee>("Olek", std::make_unique<PMRole>());

        regular->set_direct_manager(pm);

        auto expense = Expense("conference", 2'000);
        ASSERT_EQ(regular->get_approver(expense), "Olek");
    }

    TEST(AcceptanceSystem, LargeExpenseDirectorShouldAccept) {
        auto regular = std::make_unique<Employee>("Grzesiu", std::make_unique<RegularRole>());
        auto pm = std::make_shared<Employee>("Olek", std::make_unique<PMRole>());
        auto director = std::make_shared<Employee>("Witek", std::make_unique<DirectorRole>());

        regular->set_direct_manager(pm);
        pm->set_direct_manager(director);

        auto expense = Expense("team integration", 20'000);
        ASSERT_EQ(regular->get_approver(expense), "Witek");
    }

    TEST(AcceptanceSystem, EnormousExpenseOnlyCEOShouldAccept) {
        auto pm = std::make_shared<Employee>("Olek", std::make_unique<PMRole>());
        auto director = std::make_shared<Employee>("Witek", std::make_unique<DirectorRole>());
        auto ceo = std::make_shared<Employee>("Andrzej", std::make_unique<CEORole>());

        pm->set_direct_manager(director);
        director->set_direct_manager(ceo);

        auto expense = Expense("company jet", 2'000'000);
        ASSERT_EQ(pm->get_approver(expense), "Andrzej");
    }
    TEST(AcceptanceSystem, TooLargeToAcceptAndNoManagerPowerfulEnoughShouldThrow) {
        auto regular = std::make_unique<Employee>("Grzesiu", std::make_unique<RegularRole>());
        auto pm = std::make_shared<Employee>("Olek", std::make_unique<PMRole>());
        auto director = std::make_shared<Employee>("Witek", std::make_unique<DirectorRole>());

        regular->set_direct_manager(pm);
        pm->set_direct_manager(director);

        auto expense = Expense("company jet", 2'000'000);
        ASSERT_THROW((void)regular->get_approver(expense), std::runtime_error);
    }
}