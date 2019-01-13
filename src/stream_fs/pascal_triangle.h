#pragma once

namespace cppchallenge::stream_fs {
    /**
     * Prints a pascal triangle
     * @param out stream
     * @param rows to print
     */
    void print_pascal_triangle(std::ostream &out, uint8_t rows) {
        for (int row(0), val(1); row < rows; ++row) {
            std::fill_n(std::ostream_iterator<char>(out), rows - row - 1, ' ');
            for (int side = 0; side <= row; ++side) {
                val = side == 0 || row == 0 ? 1 : val * (row - side + 1) / side;
                out << val;

                if (side < row) {
                    out << ' ';
                }
            }
            out << '\n';
        }
    }
}
