#include "parallel_transform.h"

#include <chrono>
#include <iostream>


int main() {
    using cppchallenge::concurrency::parallel_transform;
    static const auto DATA_SIZE = 200000;
    {
        auto test_data = std::vector<int>(DATA_SIZE);
        std::iota(test_data.begin(), test_data.end(), 1);

        auto start = std::chrono::high_resolution_clock::now();
        parallel_transform(test_data, [](const auto &el) {
            return el + 1;
        });
        auto end = std::chrono::high_resolution_clock::now();

        auto total_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Parallel: " << total_time.count() << '\n';
    }
    {
        auto test_data = std::vector<int>(DATA_SIZE);
        std::iota(test_data.begin(), test_data.end(), 1);
        auto dummy_out = std::vector<int>(DATA_SIZE);

        auto start = std::chrono::high_resolution_clock::now();
        std::transform(test_data.begin(), test_data.end(), dummy_out.begin(), [](const auto &el) {
            return el + 1;
        });
        auto end = std::chrono::high_resolution_clock::now();

        auto total_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Sequential: " << total_time.count() << '\n';
    }
}
