#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <random>
#include <memory>
#include "../../src/math/compute_pi.h"

namespace {
    using namespace testing;

    class ComputePiTest : public Test {
    protected:
        void SetUp() override {
            auto seed_data = std::array<int, std::mt19937::state_size>{};
            std::generate(seed_data.begin(), seed_data.end(), std::ref(rd));
            std::seed_seq seq(seed_data.begin(), seed_data.end());

            engine = std::make_unique<std::mt19937>(seq);

            distribution = std::make_unique<std::uniform_real_distribution<>>(std::uniform_real_distribution<>{0, 1});
        }

        auto &get_distribution() {
            return distribution;
        }

        auto &get_engine() {
            return engine;
        }

    private:
        std::default_random_engine rd;
        std::unique_ptr<std::uniform_real_distribution<>> distribution;
        std::unique_ptr<std::mt19937> engine;
    };

    TEST_F(ComputePiTest, GivenZeroSamplesShouldThrow) {
        ASSERT_THROW(cppchallenge::math::compute_pi(*get_engine(), *get_distribution(), 0), std::invalid_argument);
    }

    TEST_F(ComputePiTest, GivenManySamplesShouldCalculatePi) {
        ASSERT_THAT(cppchallenge::math::compute_pi(*get_engine(), *get_distribution()), DoubleNear(3.14, 0.01));
    }
}