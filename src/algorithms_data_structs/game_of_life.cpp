#include <random>
#include "game_of_life.h"

namespace cppchallenge::algorithms_data_structs::game_of_life {
    World::World(size_t width, size_t height) :  width(width), height(height), _map(create_empty_world(width, height)) {
    }

    bool World::get(size_t x, size_t y) const {
        return _map[x][y];
    }

    void World::set(size_t x, size_t y, bool value) {
        _map[y][x] = value;
    }

    void World::display(std::ostream &out) const {
        for (const auto& row : _map) {
            for (const auto& cell : row) {
                out << (cell ? 'x' : '.');
            }
            out << '\n';
        }
    }

    void World::simulate() {
        auto next_map = create_empty_world(width, height);
        for (auto y{0u}; y < height; ++y) {
            for (auto x{0u}; x < width; ++x) {
                auto neighbours = count_neighbours(x, y);

                if (_map[y][x]) {
                    // die if underpopulated or overpopulated, live otherwise
                    next_map[y][x] = !(neighbours < 2 || neighbours > 3);
                } else {
                    // create life by reproduction
                    next_map[y][x] = neighbours == 3;
                }
            }
        }

        _map = next_map;
    }

    size_t World::count_neighbours(size_t x, size_t y) const {
        auto neighbours{0u};

        // xxx
        // ...
        // ...
        if (y > 0) {
            if (x > 0 && _map[y - 1][x - 1]) ++neighbours;
            if (_map[y - 1][x]) ++neighbours;
            if (x < width - 1 && _map[y - 1][x + 1]) ++neighbours;
        }

        // ...
        // x.x
        // ...
        if (x > 0 && _map[y][x - 1]) ++neighbours;
        if (x < width - 1 && _map[y][x + 1]) ++neighbours;

        // ...
        // ...
        // xxx
        if (y < height - 1) {
            if (x > 0 && _map[y + 1][x - 1]) ++neighbours;
            if (_map[y + 1][x]) ++neighbours;
            if (x < width - 1 && _map[y + 1][x + 1]) ++neighbours;
        }

        return neighbours;
    }

    World::world_data_type World::create_empty_world(size_t width, size_t height) {
        return std::vector<std::vector<bool>>{height, std::vector<bool>(width)};
    }

    void CrazyWorld::randomize(std::mt19937& mt) {
        std::uniform_int_distribution dist(0,1);

        for (auto y{0u}; y < height; ++y) {
            for (auto x{0u}; x < width; ++x) {
                set(x,y, dist(mt) % 2);
            }
        }
    }

    CrazyWorld::CrazyWorld(size_t width, size_t height) : World(width, height) {}
}
