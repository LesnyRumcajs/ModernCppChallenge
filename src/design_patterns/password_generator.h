#pragma once

#include <string>
#include <memory>
#include <random>
#include <algorithm>

namespace cppchallenge::design_patterns {

    /**
     * Password generator interface
     */
    class PasswordGenerator {
    public:
        virtual std::string generate() = 0;

        [[nodiscard]] virtual std::string allowed_chars() const = 0;

        [[nodiscard]] virtual size_t get_length() const = 0;

        virtual void add(std::unique_ptr<PasswordGenerator> generator) = 0;

        virtual ~PasswordGenerator() = default;
    };

    class BasicPasswordGenerator : public PasswordGenerator {
    public:
        explicit BasicPasswordGenerator(size_t password_length) noexcept : password_length(password_length) {}

        [[nodiscard]]size_t get_length() const noexcept final {
            return password_length;
        }

    private:
        std::string generate() override {
            throw std::runtime_error("Not implemented!");
        }

        void add(std::unique_ptr<PasswordGenerator>) override {
            throw std::runtime_error("Not implemented!");
        }


    private:
        size_t password_length;
    };

    class DigitGenerator final : public BasicPasswordGenerator {
    public:
        explicit DigitGenerator(size_t password_length) noexcept : BasicPasswordGenerator(password_length) {}

        [[nodiscard]]std::string allowed_chars() const override {
            return "0123456789";
        }
    };

    class SymbolGenerator final : public BasicPasswordGenerator {
    public:
        explicit SymbolGenerator(size_t password_length) noexcept  : BasicPasswordGenerator(password_length) {}

        [[nodiscard]]std::string allowed_chars() const override {
            return "!@#$%^&*()_+{}[]<>,.";
        }
    };

    class UpperLetterGenerator final : public BasicPasswordGenerator {
    public:
        explicit UpperLetterGenerator(size_t password_length) noexcept  : BasicPasswordGenerator(password_length) {}

        [[nodiscard]]std::string allowed_chars() const override {
            return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        }
    };

    class LowerLetterGenerator final : public BasicPasswordGenerator {
    public:
        explicit LowerLetterGenerator(size_t password_length) noexcept  : BasicPasswordGenerator(password_length) {}

        [[nodiscard]]std::string allowed_chars() const override {
            return "abcdefghijklmnopqrstuvwxyz";
        }
    };

    class CompositePasswordGenerator final : public PasswordGenerator {
    public:
        CompositePasswordGenerator() {
            auto seed_data = std::array<int, std::mt19937::state_size>{};
            std::generate(seed_data.begin(), seed_data.end(), std::ref(rd));
            std::seed_seq seq(seed_data.begin(), seed_data.end());
            eng.seed(seq);
        }

        std::string generate() override {
            std::string password;
            for (const auto &generator : generators) {
                const auto chars = generator->allowed_chars();
                std::uniform_int_distribution dist(0, static_cast<int>(chars.length() - 1));

                for (size_t i(0); i < generator->get_length(); ++i) {
                    password += chars[dist(eng)];
                }
            }
            std::shuffle(password.begin(), password.end(), eng);
            return password;
        }

        void add(std::unique_ptr<PasswordGenerator> generator) override {
            generators.emplace_back(std::move(generator));
        }

    private:
        std::default_random_engine rd;
        std::mt19937 eng;
        std::vector<std::unique_ptr<PasswordGenerator>> generators;

        [[nodiscard]]std::string allowed_chars() const override {
            throw std::runtime_error("Not implemented!");
        }

        [[nodiscard]]size_t get_length() const override {
            throw std::runtime_error("Not implemented!");
        }
    };
}