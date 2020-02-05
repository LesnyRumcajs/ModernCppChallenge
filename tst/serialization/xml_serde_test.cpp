#include <filesystem>
#include <fstream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include "../../src/serialization/xml_serde.h"

namespace {
    using namespace testing;
    using namespace cppchallenge::serialization;

    const auto xml_no_movies = std::filesystem::path("../tst/res/serialization/no_movies.xml");
    const auto xml_one_movie = std::filesystem::path("../tst/res/serialization/one_movie.xml");
    const auto xml_two_movies = std::filesystem::path("../tst/res/serialization/two_movies.xml");

    auto get_contents(const std::filesystem::path& path) -> std::string {
        std::ifstream ifs(path);
        return {(std::istreambuf_iterator<char>(ifs)),std::istreambuf_iterator<char>()};
    }

    const auto movie_1 = Movie {
            0,
            "Phantom Menace",
            1997,
            120,
            {"George Lucas"},
            {"No idea"},
            {
                    {"Obi Wan Kenobi", "Evan McGregor"},
                    {"Qui Gon Jinn", "Liam Neeson"}
            }
    };

    const auto movie_2 = Movie {
            1,
            "Revenge of the Sith",
            2004,
            123,
            {"George Lucas"},
            {"No idea"},
            {
                    {"Obi Wan Kenobi", "Evan McGregor"},
                    {"Anakin Skywalker", "Hayden Christensen"}
            }
    };

    TEST(Serialization, NoMoviesEmptyXml) {
        auto movies = std::vector<Movie>();
        auto temp_file = std::filesystem::temp_directory_path() / "no_movies.xml";

        {
            std::ofstream ofs(temp_file);
            boost::archive::xml_oarchive oa(ofs, boost::archive::no_header);
            oa << BOOST_SERIALIZATION_NVP(movies);
        }

        auto actual = get_contents(temp_file);
        auto expected = get_contents(xml_no_movies);

        ASSERT_EQ(actual, expected);
    }

    TEST(Serialization, OneMovie) {
        auto movies = std::vector<Movie>{movie_1};
        auto temp_file = std::filesystem::temp_directory_path() / "one_movie.xml";

        {
            std::ofstream ofs(temp_file);
            boost::archive::xml_oarchive oa(ofs, boost::archive::no_header);
            oa << BOOST_SERIALIZATION_NVP(movies);
        }

        auto actual = get_contents(temp_file);
        auto expected = get_contents(xml_one_movie);

        ASSERT_EQ(actual, expected);
    }

    TEST(Serialization, TwoMovies) {
        auto movies = std::vector<Movie>{movie_1, movie_2};
        auto temp_file = std::filesystem::temp_directory_path() / "two_movies.xml";

        {
            std::ofstream ofs(temp_file);
            boost::archive::xml_oarchive oa(ofs, boost::archive::no_header);
            oa << BOOST_SERIALIZATION_NVP(movies);
        }

        auto actual = get_contents(temp_file);
        auto expected = get_contents(xml_two_movies);

        ASSERT_EQ(actual, expected);
    }

    TEST(Deserialization, FromEmpty) {
        std::vector<Movie> movies;
        {
            std::ifstream ifs(xml_no_movies);
            boost::archive::xml_iarchive ia(ifs, boost::archive::no_header);
            ia >> BOOST_SERIALIZATION_NVP(movies);
        }
        ASSERT_THAT(movies, IsEmpty());
    }

    TEST(Deserialization, FromOneMovie) {
        std::vector<Movie> movies;
        {
            std::ifstream ifs(xml_one_movie);
            boost::archive::xml_iarchive ia(ifs, boost::archive::no_header);
            ia >> BOOST_SERIALIZATION_NVP(movies);
        }
        ASSERT_THAT(movies, SizeIs(1));
        ASSERT_EQ(movie_1, movies.front());
    }

    TEST(Deserialization, FromTwoMovies) {
        std::vector<Movie> movies;
        {
            std::ifstream ifs(xml_two_movies);
            boost::archive::xml_iarchive ia(ifs, boost::archive::no_header);
            ia >> BOOST_SERIALIZATION_NVP(movies);
        }
        ASSERT_THAT(movies, SizeIs(2));
        auto expected = std::vector{movie_1, movie_2};
        ASSERT_EQ(expected, movies);
    }
}