#include "custom_service_system.h"

using namespace cppchallenge::concurrency;
int main() {
    using namespace std::chrono_literals;
    Office office;

    for (auto customer_nr(1u); customer_nr <= 25u; ++customer_nr) {
        office.add_customer(5ms);
    }
}
