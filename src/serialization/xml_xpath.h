#include <pugixml.hpp>

#include <filesystem>
#include <vector>
#include <string>
#include <sstream>

namespace cppchallenge::serialization {
    /**
     * General query function for obtaining collection of data from XML file
     */
    auto query(const std::filesystem::path& pathToXml, std::string_view queryString) -> std::vector<std::string> {
        pugi::xml_document doc;
        if (!doc.load_file(pathToXml.c_str())) {
            throw std::invalid_argument("Unable to open provided file");
        }

        pugi::xpath_query query(queryString.data());
        auto elements = query.evaluate_node_set(doc);

        std::vector<std::string> result;
        std::transform(elements.begin(), elements.end(), std::back_inserter(result), [](const auto& element) {
            return element.node().value();
        });

        return result;
    }
    /**
     * Returns the titles released after a specified year
     */
    std::vector<std::string> getTitlesReleasedAfter(const std::filesystem::path& pathToXml, int year) {
        std::stringstream ss;
        ss << "//movies/item[release_year > " << year << "]/title/text()";
        return query(pathToXml, ss.str());
    }

    /**
     * Returns names of the last actor in each file in an XML file
     */
    auto getLastActorsNames(const std::filesystem::path& pathToXml)-> std::vector<std::string> {
        return query(pathToXml, "//movies/item/cast/item[last()]/name/text()");
    }
}