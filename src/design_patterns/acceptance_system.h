#pragma once

#include <string>
#include <memory>
#include <utility>

// Using Chain of Responsibility design pattern
namespace cppchallenge::design_patterns {
    using CurrencyUnit = int64_t;

    /**
     * Base abstract role
     */
    class Role {
    public:
        /**
         * returns maximum amount of currency units the role can approve
         */
        [[nodiscard]]
        virtual CurrencyUnit approval_limit() const = 0;
    };

    /**
     * Role for regular employees
     */
    class RegularRole final: public Role {
    public:
        [[nodiscard]]
        CurrencyUnit approval_limit() const override {
            return 1'000;
        }
    };

    /**
     * Role for Project Manager
     */
    class PMRole final : public Role {
    public:
        [[nodiscard]] CurrencyUnit approval_limit() const override {
            return 10'000;
        }
    };

    /**
     * Role for Director
     */
    class DirectorRole final : public Role {
    public:
        [[nodiscard]] CurrencyUnit approval_limit() const override {
            return 100'000;
        }
    };

    /**
     * The role for CEO. Unlimited power!
     */
    class CEORole final : public Role {
    public:
        [[nodiscard]] CurrencyUnit approval_limit() const override {
            return std::numeric_limits<CurrencyUnit>::max();
        }
    };

    class Expense final{
    public:
        Expense(std::string_view name, const CurrencyUnit amount) : name(name), amount(amount) {}

        [[nodiscard]] CurrencyUnit get_amount() const {
            return amount;
        }

    private:
        const std::string name;
        const CurrencyUnit amount;
    };


    class Employee final {
    public:
        Employee(std::string_view name, std::unique_ptr<Role> role) : name(name), role(std::move(role)) {}

        void set_direct_manager(std::shared_ptr<Employee> manager) {
            direct_manager = std::move(manager);
        }

        /**
         * Returns the name of the employee that can approve the expense - either this employee
         * or any manager in line. Throws exception if nobody can approve.
         */
        [[nodiscard]] std::string get_approver(const Expense& expense) const {
            if (role->approval_limit() >= expense.get_amount()) {
                return name;
            }

            if (direct_manager) {
                return direct_manager->get_approver(expense);
            }

            throw std::runtime_error("No manager powerful enough to approve the expense!");
        }

    private:
        const std::string name;
        std::unique_ptr<Role> role;
        std::shared_ptr<Employee> direct_manager;
    };
}