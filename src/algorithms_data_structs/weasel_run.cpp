#include <iostream>
#include "weasel_program.h"

int main(void) {
    std::cout << "Weasel simulation start:\n";

    auto simulation = cppchallenge::algorithms_data_structs::Weasel();
    simulation.print = true;

    auto iteration_count = simulation.simulate("METHINKS IT IS LIKE A WEASEL", 0.05);

    std::cout << "Weasel simulation finished. Iterations: " << iteration_count << '\n';
}
