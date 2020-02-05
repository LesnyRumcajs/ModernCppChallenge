#pragma once

#include <string>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>

namespace cppchallenge::serialization {
    struct Role {
        friend class boost::serialization::access;
        template <typename Archive>
        void serialize(Archive& ar, const unsigned /*version*/) {
            ar & BOOST_SERIALIZATION_NVP(actor);
            ar & BOOST_SERIALIZATION_NVP(name);
        }

        std::string actor;
        std::string name;

        bool operator==(const Role &rhs) const {
            return actor == rhs.actor &&
                   name == rhs.name;
        }

        bool operator!=(const Role &rhs) const {
            return !(rhs == *this);
        }
    };

    struct Movie {
        friend class boost::serialization::access;
        template <typename Archive>
        void serialize(Archive& ar, const unsigned /*version*/) {
            ar & BOOST_SERIALIZATION_NVP(id);
            ar & BOOST_SERIALIZATION_NVP(title);
            ar & BOOST_SERIALIZATION_NVP(release_year);
            ar & BOOST_SERIALIZATION_NVP(duration_min);
            ar & BOOST_SERIALIZATION_NVP(directors);
            ar & BOOST_SERIALIZATION_NVP(authors);
            ar & BOOST_SERIALIZATION_NVP(cast);
        }

        uint32_t id;
        std::string title;
        uint32_t release_year;
        uint32_t duration_min;
        std::vector<std::string> directors;
        std::vector<std::string> authors;
        std::vector<Role> cast;

        bool operator==(const Movie &rhs) const {
            return id == rhs.id &&
                   title == rhs.title &&
                   release_year == rhs.release_year &&
                   duration_min == rhs.duration_min &&
                   directors == rhs.directors &&
                   authors == rhs.authors &&
                   cast == rhs.cast;
        }

        bool operator!=(const Movie &rhs) const {
            return !(rhs == *this);
        }
    };
}
