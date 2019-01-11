#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/string/parse_uri.h"

namespace {
    using namespace cppchallenge::string;
    using namespace std::string_literals;
    using namespace testing;

    TEST(ParseURI_Test, GivenInvalidUriShouldReturnNullOpt) {
        ASSERT_FALSE(parse_uri(""));
        ASSERT_FALSE(parse_uri("1234"));
        ASSERT_FALSE(parse_uri("http:/www.google.com"));
    }

    TEST(ParseURI_Test, GivenValidUriShouldReturnCorrectPartsOnlyProtocolDomain) {
        auto result = parse_uri("https://test"s);

        ASSERT_TRUE(result);
        ASSERT_EQ(result->protocol, "https");
        ASSERT_EQ(result->domain, "test");
    }

    TEST(ParseURI_Test, GivenValidUriShouldReturnCorrectPartsEverything) {
        auto result = parse_uri("http://test.org:42/some/path/asset.html?arg=foo#bar");

        ASSERT_TRUE(result);
        ASSERT_EQ(result->protocol, "http");
        ASSERT_EQ(result->domain, "test.org");
        ASSERT_EQ(result->port, 42);
        ASSERT_EQ(result->path.value(), "/some/path/asset.html");
        ASSERT_EQ(result->query.value(), "arg=foo");
        ASSERT_EQ(result->fragment.value(), "bar");
    }
}
