#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/lang/IPv4.h"

namespace {
    using namespace cppchallenge::lang;
    const std::string DEFAULT_IP{"0.0.0.0"};
    const std::string TEST_IP{"192.168.0.1"};

//     TEST(IPv4Test, ShouldDefaultToZeroes) {
//         ASSERT_EQ(IPv4().to_string(), DEFAULT_IP);
//     }

//     TEST(IPv4Test, ShouldCorrectlyParseString) {
//         ASSERT_EQ(IPv4().from_string(TEST_IP).to_string(), TEST_IP);
//     }

//     TEST(IPv4Test, ShouldCorrectlyOutputToStdout) {
//         testing::internal::CaptureStdout();
//         std::cout << IPv4().from_string(TEST_IP);
//         ASSERT_EQ(TEST_IP, testing::internal::GetCapturedStdout());
//     }

//     TEST(IPv4Test, ShouldCorrectlyGetFromIStream) {
//         std::stringstream ss;
//         ss << TEST_IP;

//         IPv4 iPv4;
//         ss >> iPv4;

//         ASSERT_EQ(iPv4.to_string(), TEST_IP);
//     }

//     TEST(IPv4Test, GivenInvalidOctetCountShouldThrow) {
//         ASSERT_THROW(IPv4().from_string("1.2.3"), std::invalid_argument);
//         ASSERT_THROW(IPv4().from_string("1.2.3.4.5"), std::invalid_argument);
//         ASSERT_THROW(IPv4().from_string("1"), std::invalid_argument);
//     }

//     TEST(IPv4Test, GivenInvalidOctetShouldThrow) {
//         ASSERT_THROW(IPv4().from_string("1.2.3.a"), std::invalid_argument);
//         ASSERT_THROW(IPv4().from_string("a.b.c.d"), std::invalid_argument);
//         ASSERT_THROW(IPv4().from_string("-23.0.-0.0"), std::invalid_argument);
//     }

//     TEST(IPv4Test, ShouldCorrectlyConvertToNumber) {
//         ASSERT_EQ(IPv4().from_string("0.0.0.1").to_num(), 1);
//         ASSERT_EQ(IPv4().from_string("127.0.0.1").to_num(), 2130706433);
//     }

//     TEST(IPv4Test, ShouldCorrectlyCreateFromNum) {
//         ASSERT_EQ(IPv4(2130706433).to_string(), "127.0.0.1");
//         ASSERT_EQ(IPv4(0).to_string(), "0.0.0.0");
//     }

//     TEST(IPv4Test, ShouldCorrectlyCompareEqualIPv4Objects) {
//         ASSERT_TRUE(IPv4(TEST_IP) == IPv4(192, 168, 0, 1));
//     }

//     TEST(IPv4Test, ShouldCorrectlyCompareLesserIPv4Objects) {
//         ASSERT_TRUE(IPv4(127, 0, 0, 1) < IPv4(192, 168, 0, 0));
//         ASSERT_TRUE(IPv4(0, 0, 0, 1) < IPv4(0, 0, 0, 2));
//         ASSERT_FALSE(IPv4(1, 1, 1, 1) < IPv4(1, 1, 1, 1));
//     }

//     TEST(IPv4Test, ShouldCorrectlyCompareLesserEqualIPv4Objects) {
//         ASSERT_TRUE(IPv4(0, 0, 0, 1) <= IPv4(0, 0, 0, 2));
//         ASSERT_TRUE(IPv4(1, 1, 1, 1) <= IPv4(1, 1, 1, 1));
//     }

//     TEST(CreateIPv4Range, ShouldCorrectlyGenerateRangeOfIPv4s) {
//         ASSERT_THAT(create_ipv4_range(IPv4(0, 0, 0, 1), IPv4(0, 0, 0, 3)), testing::ElementsAre(
//                 IPv4(0, 0, 0, 1),
//                 IPv4(0, 0, 0, 2),
//                 IPv4(0, 0, 0, 3)
//         ));

//         ASSERT_THAT(create_ipv4_range(IPv4(192, 168, 0, 254), IPv4(192, 168, 1, 1)), testing::ElementsAre(
//                 IPv4(192, 168, 0, 254),
//                 IPv4(192, 168, 0, 255),
//                 IPv4(192, 168, 1, 0),
//                 IPv4(192, 168, 1, 1)
//         ));
//     }

//     TEST(CreateIPv4Range, ShouldThrowGivenIncorrectRange) {
//         ASSERT_THROW(create_ipv4_range(IPv4(0, 0, 0, 3), IPv4(0, 0, 0, 1)), std::invalid_argument);
//     }
}
