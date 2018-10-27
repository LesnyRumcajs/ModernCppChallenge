#pragma once

#include <random>
#include <stdexcept>

namespace cppchallenge::math {
    /**
     * Calculates the PI value using Monte Carlo method. Algorithm is as follows:
     * 1. Generate sample positions (x,y) in a square of side 1 (d^2)
     * 2. Count each position that would fit in a circle of diameter of 1 (pi*d^2 / 4)
     * 3. Divide each other and mutliply by four.
     *
     * @tparam Engine
     * @tparam Distribution
     * @param engine
     * @param distribution
     * @param SAMPLES
     * @return value of PI
     */
    template<typename Engine = std::mt19937,
            typename Distribution = std::uniform_real_distribution<>>
    double compute_pi(Engine &engine, Distribution &distribution, const unsigned SAMPLES = 1'000'000) {
        if (SAMPLES == 0) {
            throw std::invalid_argument("Invalid number of samples");
        }

        auto hits_in_circle = 0u;
        for (auto i = 0u; i < SAMPLES; ++i) {
            auto x = distribution(engine);
            auto y = distribution(engine);

            if (std::pow(x, 2) + std::pow(y, 2) <= 1) {
                ++hits_in_circle;
            }
        }

        return 4.0 * (hits_in_circle * 1.0 / SAMPLES);
    }
}