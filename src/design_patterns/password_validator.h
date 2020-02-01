#pragma once

#include <memory>
#include <string_view>

namespace cppchallenge::design_patterns {
    /**
     * Base interface for implementing password validation
     */
    class PasswordValidator {
    public:
        virtual auto validate(std::string_view password) -> bool = 0;

        virtual ~PasswordValidator() = default;
    };

    /**
     * Obligatory validator. Validation of length
     */
    class LengthValidator final : public PasswordValidator {
    public:
        explicit LengthValidator(unsigned min_length) : min_length(min_length) {}

        auto validate(std::string_view password) -> bool override {
            return password.length() >= min_length;
        }

    private:
        unsigned min_length;
    };

    /**
     * Decorator for PasswordValidator.
     */
    class PasswordValidatorDecorator : public PasswordValidator {
    public:
        explicit PasswordValidatorDecorator(std::unique_ptr<PasswordValidator> validator) : inner(
                std::move(validator)) {}

        auto validate(std::string_view password) -> bool override {
            return inner->validate(password);
        }

    private:
        std::unique_ptr<PasswordValidator> inner;
    };

    /**
     * Validates that the password contains digits
     */
    class DigitPasswordValidator final : public PasswordValidatorDecorator {
    public:
        explicit DigitPasswordValidator(std::unique_ptr<PasswordValidator> validator) : PasswordValidatorDecorator(
                std::move(validator)) {
        }

        auto validate(std::string_view password) -> bool override {
            return PasswordValidatorDecorator::validate(password) &&
                   password.find_first_of("0123456789") != std::string::npos;
        }
    };

    /**
     * Validates that the password contains case-different letters
     */
    class CasePasswordValidator final : public PasswordValidatorDecorator {
    public:
        explicit CasePasswordValidator(std::unique_ptr<PasswordValidator> validator) : PasswordValidatorDecorator(
                std::move(validator)) {
        }

        auto validate(std::string_view password) -> bool override {
            if (!PasswordValidatorDecorator::validate(password)) { return false;
}

            bool has_lower = false, has_upper = false;

            for (const auto ch : password) {
                if (std::islower(ch)) {
                    has_lower = true;
                } else if (std::isupper(ch)) {
                    has_upper = true;
                }

                if (has_lower && has_upper) { return true;
}
            }

            return false;
        }
    };

    /**
     * Validates that the password contains symbols
     */
    class SymbolPasswordValidator final : public PasswordValidatorDecorator {
    public:
        explicit SymbolPasswordValidator(std::unique_ptr<PasswordValidator> validator) : PasswordValidatorDecorator(
                std::move(validator)) {
        }

        auto validate(std::string_view password) -> bool override {
            return PasswordValidatorDecorator::validate(password) &&
                   password.find_first_of("!@#$%^&*(){}[]?<>") != std::string::npos;
        }
    };
}
