#pragma once

#include <vector>
#include <iostream>
#include <random>

namespace cppchallenge::algorithms_data_structs::game_of_life {
    class World {
    public:
        size_t width;
        size_t height;

        /**
         * Creates world of the given dimensions
         */
        World(size_t width, size_t height);

        /**
         * Displays the current world's state
         * @param out output stream
         */
        void display(std::ostream& out = std::cout) const;

        /**
         * Returns the value at the given world coordinates
         */
        bool get(size_t x, size_t y) const;

        /**
         * Sets the value at the given world coordinates
         */
        void set(size_t x, size_t y, bool value);

        /**
         * Runs the simulation - creates next world's generation
         */
        void simulate();
    private:
        using world_data_type = std::vector<std::vector<bool>>;
        world_data_type _map;

        /**
         * Counts neighbours of a given point
         */
        size_t count_neighbours(size_t x, size_t y) const;

        static world_data_type create_empty_world(size_t width, size_t height);
    };

    class CrazyWorld : public World {
    public:
        /**
         * Completely randomizes the current world!
         */
        void randomize(std::mt19937& mt);

        CrazyWorld(size_t width, size_t height);
    };
}
