#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/design_patterns/password_generator.h"

namespace {
    using namespace testing;
    using namespace cppchallenge::design_patterns;

    TEST(PasswordGenerator, DifferentPasswords) {
        CompositePasswordGenerator generator;
        generator.add(std::make_unique<LowerLetterGenerator>(5));

        auto password1 = generator.generate();
        auto password2 = generator.generate();

        ASSERT_NE(password1, password2);
    }

    TEST(PasswordGenerator, CompositeWithZeroLength) {
        CompositePasswordGenerator generator;
        generator.add(std::make_unique<LowerLetterGenerator>(0));

        auto password = generator.generate();

        ASSERT_THAT(password, IsEmpty());
    }

    TEST(PasswordGenerator, CompositeLowerAndUpperCase) {
        CompositePasswordGenerator generator;
        generator.add(std::make_unique<LowerLetterGenerator>(1));
        generator.add(std::make_unique<UpperLetterGenerator>(1));

        auto password = generator.generate();

        ASSERT_EQ(password.length(), 2);
        ASSERT_TRUE(password.find_first_of("abcdefghijklmnopqrstuvwxyz") != std::string::npos);
        ASSERT_TRUE(password.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos);
    }

    TEST(PasswordGenerator, CompositeAll) {
        CompositePasswordGenerator generator;
        generator.add(std::make_unique<LowerLetterGenerator>(1));
        generator.add(std::make_unique<UpperLetterGenerator>(1));
        generator.add(std::make_unique<SymbolGenerator>(1));
        generator.add(std::make_unique<DigitGenerator>(1));

        auto password = generator.generate();

        ASSERT_EQ(password.length(), 4);
        ASSERT_TRUE(password.find_first_of("abcdefghijklmnopqrstuvwxyz") != std::string::npos);
        ASSERT_TRUE(password.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos);
        ASSERT_TRUE(password.find_first_of("123456890") != std::string::npos);
        ASSERT_TRUE(password.find_first_of("!@#$%^&*()_+{}[]<>,.") != std::string::npos);
    }
}