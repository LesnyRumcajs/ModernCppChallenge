#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/design_patterns/password_validator.h"

namespace {
    using namespace testing;
    using namespace cppchallenge::design_patterns;

    TEST(PasswordValidatorTest, LengthValidatorOnly) {
       auto validator = std::make_unique<LengthValidator>(8);
       ASSERT_FALSE(validator->validate("0"));
       ASSERT_FALSE(validator->validate("123"));
       ASSERT_FALSE(validator->validate("1234567"));
       ASSERT_TRUE(validator->validate("12345678"));
       ASSERT_TRUE(validator->validate("123456789"));
    }

    TEST(PasswordValidatorTest, DigitPasswordValidator) {
        auto validator = std::make_unique<DigitPasswordValidator>(std::make_unique<LengthValidator>(3));
        ASSERT_FALSE(validator->validate(""));
        ASSERT_FALSE(validator->validate("abcd"));
        ASSERT_FALSE(validator->validate("2!"));

        ASSERT_TRUE(validator->validate("123"));
        ASSERT_TRUE(validator->validate("ab2"));
        ASSERT_TRUE(validator->validate("abcd!1"));
    }

    TEST(PasswordValidatorTest, CasePasswordValidator) {
        auto validator = std::make_unique<CasePasswordValidator>(std::make_unique<LengthValidator>(3));
        ASSERT_FALSE(validator->validate(""));
        ASSERT_FALSE(validator->validate("abcd"));
        ASSERT_FALSE(validator->validate("a2!"));

        ASSERT_TRUE(validator->validate("AbC"));
        ASSERT_TRUE(validator->validate("AAA1b"));
    }

    TEST(PasswordValidatorTest, SymbolPasswordValidator) {
        auto validator = std::make_unique<SymbolPasswordValidator>(std::make_unique<LengthValidator>(3));
        ASSERT_FALSE(validator->validate(""));
        ASSERT_FALSE(validator->validate("abcd"));
        ASSERT_FALSE(validator->validate("a2A"));

        ASSERT_TRUE(validator->validate("Ab!"));
        ASSERT_TRUE(validator->validate("11!"));
    }

    TEST(PasswordValidator, CaseAndDigitsValidator) {
        auto validator = std::make_unique<DigitPasswordValidator>(
                std::make_unique<CasePasswordValidator>(
                        std::make_unique<LengthValidator>(3)));

        ASSERT_FALSE(validator->validate(""));
        ASSERT_FALSE(validator->validate("123ab"));
        ASSERT_FALSE(validator->validate("AAAA!"));

        ASSERT_TRUE(validator->validate("AAAa1"));
        ASSERT_TRUE(validator->validate("aB1"));
        ASSERT_TRUE(validator->validate("!!!!abcC1"));
    }

    TEST(PasswordValidator, CaseDigitsSymbolValidator) {
        auto validator = std::make_unique<DigitPasswordValidator>(
                std::make_unique<CasePasswordValidator>(
                        std::make_unique<SymbolPasswordValidator>(
                        std::make_unique<LengthValidator>(3))));


        ASSERT_FALSE(validator->validate(""));
        ASSERT_FALSE(validator->validate("123abC"));
        ASSERT_FALSE(validator->validate("AAAA!aaa"));

        ASSERT_TRUE(validator->validate("AAAa1!"));
        ASSERT_TRUE(validator->validate("a%B1"));
        ASSERT_TRUE(validator->validate("!!!!abcC1"));
    }
}
