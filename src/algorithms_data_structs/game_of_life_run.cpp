#include "game_of_life.h"


#include <chrono>
#include <thread>
#include <random>

void clear_console();

int main() {
    using namespace cppchallenge::algorithms_data_structs::game_of_life;
    using namespace std::chrono_literals;

    CrazyWorld world(50,30);

    std::default_random_engine rd;
    std::mt19937 mt(rd());

    world.randomize(mt);
    while (true) {
        clear_console();

        world.display();
        world.simulate();

        std::this_thread::sleep_for(500ms);
    }
}

void clear_console() { std::cout << "\033[2J\033[1;1H"; }
