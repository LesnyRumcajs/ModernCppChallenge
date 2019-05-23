#pragma once

#include <string>
#include <random>
#include <memory>

namespace cppchallenge::algorithms_data_structs {
    class Weasel {
    public:
        Weasel();
        Weasel(const Weasel& ) = delete;
        Weasel&operator=(const Weasel& ) = delete;

        /**
         * Starts the simulation
         * @param phrase target phrase
         * @return Number of iterations needed to create phrase
         */
        size_t simulate(std::string_view phrase, const double mutation_chance) const;

        /**
         * Print to stdout
         */
        bool print = false;
    private:
        /**
         * Initializes randomness
         */
        void initialize_random();

        mutable std::shared_ptr<std::mt19937> mt;
    };

    class WeaselPhrase {
    public:
        WeaselPhrase(std::shared_ptr<std::mt19937> mt, size_t phrase_length);
        WeaselPhrase(std::shared_ptr<std::mt19937> mt, std::string phrase);
        WeaselPhrase(const WeaselPhrase& rhs) = default;
        WeaselPhrase& operator=(const WeaselPhrase& rhs) = default;

        /**
         * Replicates the phrase with a given chance of mutation
         */
        WeaselPhrase replicate(double mutation_chance) const;

        /**
         * Checks if the given string is the same as the underlying phrase
         */
        bool is_same(std::string_view candidate) const;

        /**
         * Scores the phrase based on letter matches (position and character)
         */
        size_t score(std::string_view candidate_phrase) const;

        /**
         * Returns a copy of the phrase
         */
        std::string get_phrase() const;
    private:
        WeaselPhrase(std::shared_ptr<std::mt19937> mt);

        /**
         * Creates a random phrase of given length
         * @return
         */
        std::string random_phrase(const size_t length) const;

        /**
         * Current phrase
         */
        std::string phrase;

        mutable std::uniform_int_distribution<> char_dist;
        mutable std::uniform_real_distribution<> mutation_dist;
        mutable std::shared_ptr<std::mt19937> mt;
    };
}
