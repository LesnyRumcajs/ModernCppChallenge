#pragma once

#include <algorithm>
#include <memory>
#include <random>
#include <string>

namespace cppchallenge::design_patterns {

    /**
     * Password generator interface
     */
    class PasswordGenerator {
    public:
        virtual auto generate() -> std::string = 0;

        [[nodiscard]] virtual auto allowed_chars() const -> std::string = 0;

        [[nodiscard]] virtual auto get_length() const -> size_t = 0;

        virtual void add(std::unique_ptr<PasswordGenerator> generator) = 0;

        virtual ~PasswordGenerator() = default;
    };

    class BasicPasswordGenerator : public PasswordGenerator {
    public:
        explicit BasicPasswordGenerator(size_t password_length) noexcept : password_length(password_length) {}

        [[nodiscard]]auto get_length() const noexcept -> size_t final {
            return password_length;
        }

    private:
        auto generate() -> std::string override {
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

        [[nodiscard]]auto allowed_chars() const -> std::string override {
            return "0123456789";
        }
    };

    class SymbolGenerator final : public BasicPasswordGenerator {
    public:
        explicit SymbolGenerator(size_t password_length) noexcept  : BasicPasswordGenerator(password_length) {}

        [[nodiscard]]auto allowed_chars() const -> std::string override {
            return "!@#$%^&*()_+{}[]<>,.";
        }
    };

    class UpperLetterGenerator final : public BasicPasswordGenerator {
    public:
        explicit UpperLetterGenerator(size_t password_length) noexcept  : BasicPasswordGenerator(password_length) {}

        [[nodiscard]]auto allowed_chars() const -> std::string override {
            return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        }
    };

    class LowerLetterGenerator final : public BasicPasswordGenerator {
    public:
        explicit LowerLetterGenerator(size_t password_length) noexcept  : BasicPasswordGenerator(password_length) {}

        [[nodiscard]]auto allowed_chars() const -> std::string override {
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

        auto generate() -> std::string override {
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

        [[nodiscard]]auto allowed_chars() const -> std::string override {
            throw std::runtime_error("Not implemented!");
        }

        [[nodiscard]]auto get_length() const -> size_t override {
            throw std::runtime_error("Not implemented!");
        }
    };
}