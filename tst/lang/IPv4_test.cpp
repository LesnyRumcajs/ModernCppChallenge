#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/lang/IPv4.h"

namespace {
    const std::string DEFAULT_IP{"0.0.0.0"};
    const std::string TEST_IP{"192.168.0.1"};

    TEST(IPv4Test, ShouldDefaultToZeroes) {
        ASSERT_EQ(cppchallenge::lang::IPv4().to_string(), DEFAULT_IP);
    }

    TEST(IPv4Test, ShouldCorrectlyParseString) {
        ASSERT_EQ(cppchallenge::lang::IPv4().from_string(TEST_IP).to_string(), TEST_IP);
    }

    TEST(IPv4Test, ShouldCorrectlyOutputToStdout) {
        testing::internal::CaptureStdout();
        std::cout << cppchallenge::lang::IPv4().from_string(TEST_IP);
        ASSERT_EQ(TEST_IP, testing::internal::GetCapturedStdout());
    }

    TEST(IPv4Test, ShouldCorrectlyGetFromIStream) {
        std::stringstream ss;
        ss << TEST_IP;

        cppchallenge::lang::IPv4 iPv4;
        ss >> iPv4;

        ASSERT_EQ(iPv4.to_string(), TEST_IP);
    }

    TEST(IPv4Test, GivenInvalidOctetCountShouldThrow) {
        ASSERT_THROW(cppchallenge::lang::IPv4().from_string("1.2.3"), std::invalid_argument);
        ASSERT_THROW(cppchallenge::lang::IPv4().from_string("1.2.3.4.5"), std::invalid_argument);
        ASSERT_THROW(cppchallenge::lang::IPv4().from_string("1"), std::invalid_argument);
    }

    TEST(IPv4Test, GivenInvalidOctetShouldThrow) {
        ASSERT_THROW(cppchallenge::lang::IPv4().from_string("1.2.3.a"), std::invalid_argument);
        ASSERT_THROW(cppchallenge::lang::IPv4().from_string("a.b.c.d"), std::invalid_argument);
        ASSERT_THROW(cppchallenge::lang::IPv4().from_string("-23.0.-0.0"), std::invalid_argument);
    }
}
