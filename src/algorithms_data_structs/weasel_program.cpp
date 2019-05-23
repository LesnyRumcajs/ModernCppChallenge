#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include "weasel_program.h"

namespace cppchallenge::algorithms_data_structs {
    namespace {
        const std::string WEASEL_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    }
    WeaselPhrase::WeaselPhrase(std::shared_ptr<std::mt19937> mt) : char_dist(0, WEASEL_CHARS.length() - 1), mutation_dist(0, 1),
                                                                   mt(std::move(mt)) {
    }

    WeaselPhrase::WeaselPhrase(std::shared_ptr<std::mt19937> mt, size_t phrase_length) :
    WeaselPhrase(mt) {
        this->phrase = random_phrase(phrase_length);
    }

    WeaselPhrase::WeaselPhrase(std::shared_ptr<std::mt19937> mt, std::string phrase) :
        WeaselPhrase(mt) {
        this->phrase = phrase;
    }

    WeaselPhrase WeaselPhrase::replicate(double mutation_chance) const {
        auto replicated_phrase = std::string{};

        std::transform(phrase.begin(), phrase.end(), std::back_inserter(replicated_phrase), [&](const auto ch) {
            return mutation_chance > mutation_dist(*mt) ? WEASEL_CHARS[char_dist(*mt)] : ch;
        });
        return WeaselPhrase(mt, replicated_phrase);
    }

    std::string WeaselPhrase::random_phrase(const size_t length) const {
        auto result = std::string{};
        std::generate_n(std::back_inserter(result), length, [&]() {
            return WEASEL_CHARS[char_dist(*mt)];
        });

        return result;
    }

    bool WeaselPhrase::is_same(std::string_view candidate) const {
        return candidate == this->phrase;
    }

    size_t WeaselPhrase::score(std::string_view candidate_phrase) const {
        const auto len = std::min(candidate_phrase.length(), this->phrase.length());

        auto score{0u};
        for (auto i{0u}; i < len; ++i) {
            if (candidate_phrase[i] == this->phrase[i]) {
                ++score;
            }
        }

        return score;
    }

    std::string WeaselPhrase::get_phrase() const {
        return phrase;
    }

    Weasel::Weasel() {
        initialize_random();
    }

    void Weasel::initialize_random() {
        std::random_device rd;
        auto seed_data = std::array<int, std::mt19937::state_size>{};
        std::generate(seed_data.begin(), seed_data.end(), std::ref(rd));

        std::seed_seq seq(seed_data.begin(), seed_data.end());
        mt = std::make_shared<std::mt19937>(seq);
    }

    size_t Weasel::simulate(std::string_view phrase, const double mutation_chance) const {
        auto weasel_phrase = WeaselPhrase(mt, phrase.length());

        auto iteration_count{0u};
        while (!weasel_phrase.is_same(phrase)) {
            std::vector<WeaselPhrase> weasels;
            std::generate_n(std::back_inserter(weasels), 100, [&]() {
                return weasel_phrase.replicate(mutation_chance);
            });

            weasel_phrase = *std::max_element(weasels.begin(), weasels.end(), [&phrase](const auto& lhs, const auto& rhs){
                return lhs.score(phrase) < rhs.score(phrase);
            });

            if (print) {
                std::cout << weasel_phrase.get_phrase() << '\n';
            }

            ++iteration_count;
        }

        return iteration_count;
    }
}
