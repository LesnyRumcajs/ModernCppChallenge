#include <filesystem>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/serialization/xml_xpath.h"

namespace {
    using namespace testing;
    using namespace cppchallenge::serialization;

    const auto xml_no_movies = std::filesystem::path("../tst/res/serialization/no_movies.xml");
    const auto xml_two_movies = std::filesystem::path("../tst/res/serialization/two_movies.xml");

    TEST(XPathTitlesReleasedAfter, GivenIncorrectFilePathShouldThrow) {
        ASSERT_THROW(getTitlesReleasedAfter(std::filesystem::path("please-don't-be-here"), 1997), std::invalid_argument);
    }

    TEST(XPathTitlesReleasedAfter, GivenCorrectFileShouldExtractAllValidTitles) {
        auto titles = getTitlesReleasedAfter(xml_two_movies, 2000);
        ASSERT_THAT(titles, ElementsAre("Revenge of the Sith"));
    }

    TEST(XPathTitlesReleasedAfter, GivenNoValidElementsShouldReturnEmpty) {
        auto titles = getTitlesReleasedAfter(xml_two_movies, 2020);
        ASSERT_THAT(titles, IsEmpty());
    }

    TEST(XPathTitlesReleasedAfter, GivenNoMoviesShouldReturnEmpty) {
        auto titles = getTitlesReleasedAfter(xml_no_movies, 1900);
        ASSERT_THAT(titles, IsEmpty());
    }

    TEST(XPathLastActorsNames, GivenIncorrectFilePathShouldThrow) {
        ASSERT_THROW(getLastActorsNames(std::filesystem::path("please-don't-be-here")), std::invalid_argument);
    }
    TEST(XPathLastActorsNames, GivenCorrectFileShouldExtractAllLastActorsNames) {
        auto names = getLastActorsNames(xml_two_movies);
        ASSERT_THAT(names, ElementsAre("Liam Neeson", "Hayden Christensen"));
    }
    TEST(XPathLastActorsNames, GivenNoMoviesShouldReturnEmpty) {
        auto names = getLastActorsNames(xml_no_movies);
        ASSERT_THAT(names, IsEmpty());
    }
}
