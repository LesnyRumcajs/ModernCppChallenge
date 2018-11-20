#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array>
#include <list>

#include "../../src/string/bin2str.h"

namespace {
    using namespace cppchallenge::string;

    TEST(bin2strTest, GivenEmptyVectorShouldReturnEmptyString) {
        ASSERT_TRUE(bin2str(std::vector<uint8_t>()).empty());
    }

    TEST(bin2strTest, GivenOneByteShouldReturnHexEncodedByte) {
        ASSERT_EQ(bin2str(std::vector<uint8_t>{0x01}), "01");
        ASSERT_EQ(bin2str(std::vector<uint8_t>{0x10}), "10");
        ASSERT_EQ(bin2str(std::vector<uint8_t>{0xaa}), "aa");
        ASSERT_EQ(bin2str(std::vector<uint8_t>{0xa0}), "a0");
    }

    TEST(bin2strTest, GivenOneByteShouldReturnHexEncodedByteUpcase) {
        ASSERT_EQ(bin2str(std::vector<uint8_t>{0xaa}, true), "AA");
        ASSERT_EQ(bin2str(std::vector<uint8_t>{0xa0}, true), "A0");
        ASSERT_EQ(bin2str(std::vector<uint8_t>{0xa0}, true), "A0");
    }

    TEST(bin2strTest, GivenMutlipleBytesShouldReturnHexEncodedBytes) {
        ASSERT_EQ(bin2str(std::vector<uint8_t>{0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF}), "0123456789abcdef");
    }

    TEST(bin2strTest, GivenMutlipleBytesShouldReturnHexEncodedBytesUpcase) {
        ASSERT_EQ(bin2str(std::vector<uint8_t>{0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF}, true), "0123456789ABCDEF");
    }

    TEST(bin2strTest, ShouldWorkOnArrays) {
        std::array<uint8_t, 5> array{0x00, 0x01, 0x00, 0xFF, 0xFE};
        ASSERT_EQ(bin2str(array, true), "000100FFFE");
    }

    TEST(bin2strTest, ShouldWorkOnLists) {
        std::list list{0x00, 0x01, 0x00, 0xFF, 0xFE};
        ASSERT_EQ(bin2str(list, true), "000100FFFE");
    }
}
