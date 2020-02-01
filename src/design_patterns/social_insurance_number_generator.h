#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <random>
#include <sstream>

namespace cppchallenge::design_patterns {
    enum class Sex {female, male};

    class SocialNumberGenerator {
    public:
        auto generate(Sex sex, unsigned year, unsigned month, unsigned day) -> std::string {
            std::stringstream social_number;
            social_number << sex_digit(sex);
            social_number << year << month << day;
            social_number << next_random(year, month, day);
            auto number = social_number.str();
            auto index = number.length();

            auto sum = std::accumulate(number.begin(), number.end(), 0, [&index](auto const sum, auto const ch){
               return sum + index-- * (ch-'0');
            });

            auto rest = sum % modulo_value();
            social_number << modulo_value() - rest;

            return  social_number.str();
        }

        virtual ~SocialNumberGenerator() = default;
    protected:
        [[nodiscard]]virtual auto sex_digit(Sex sex) const noexcept -> int = 0;

        [[nodiscard]]virtual auto next_random(unsigned year, unsigned month, unsigned day) -> int {
            auto key = year * 10000 + month * 100 + day;
            while (true) {
                auto number = dist(eng);
                auto pos = cache.find(number);
                if (pos == cache.end()) {
                    cache[key] = number;
                    return number;
                }
            }
        }

        [[nodiscard]]auto modulo_value() const noexcept -> int {
            return 11;
        }

        SocialNumberGenerator(int min, int max) : dist(min, max) {
            std::default_random_engine rd;
            auto seed_data = std::array<int, std::mt19937::state_size>{};
            std::generate(seed_data.begin(), seed_data.end(), std::ref(rd));
            std::seed_seq seq(seed_data.begin(), seed_data.end());
            eng.seed(seq);
        }

        std::mt19937 eng;
        std::uniform_int_distribution<> dist;
        std::map<unsigned, int> cache;
    };

    class SoutheriaSocialNumberGenerator final : public SocialNumberGenerator {
    public:
        SoutheriaSocialNumberGenerator() : SocialNumberGenerator(1000, 9999) {}

    protected:
        [[nodiscard]]auto sex_digit(Sex sex) const noexcept -> int override {
            return sex == Sex::female ? 1 : 2;
        }
    };

    class NortheriaSocialNumberGenerator final : public SocialNumberGenerator {
    public:
        NortheriaSocialNumberGenerator() : SocialNumberGenerator(10000, 99999) {}

    protected:
        [[nodiscard]]auto sex_digit(Sex sex) const noexcept -> int override {
            return sex == Sex::female ? 9 : 7;
        }
    };

    class SocialNumberGeneratorFactory {
    public:
        SocialNumberGeneratorFactory() {
           generators["northeria"] = std::make_unique<NortheriaSocialNumberGenerator>();
           generators["southeria"] = std::make_unique<SoutheriaSocialNumberGenerator>();
        }

        [[nodiscard]]auto getGenerator(std::string_view country) const -> SocialNumberGenerator* {
            if (auto it = generators.find(country.data()); it != generators.end()) {
                return it->second.get();
            }

            throw std::invalid_argument("Invalid country!");
        }

    private:
        std::map<std::string, std::unique_ptr<SocialNumberGenerator>> generators;
    };
}

