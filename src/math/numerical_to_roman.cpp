#include <vector>
#include "numerical_to_roman.h"

class RomanLiteral {
public:
    RomanLiteral(unsigned value, std::string label) : value(value), label(std::move(label)) {}

    const std::string &get_label() const {
        return label;
    }

    unsigned get_value() const {
        return value;
    }

private:
    unsigned value;
    std::string label;
};

std::string cppchallenge::math::numerical_to_roman(unsigned number) {
    static const std::vector<RomanLiteral> roman_literals =
            {RomanLiteral(1000, "M"),
             RomanLiteral(900, "CM"),
             RomanLiteral(500, "D"),
             RomanLiteral(400, "CD"),
             RomanLiteral(100, "C"),
             RomanLiteral(90, "XC"),
             RomanLiteral(50, "L"),
             RomanLiteral(40, "XL"),
             RomanLiteral(10, "X"),
             RomanLiteral(9, "IX"),
             RomanLiteral(5, "V"),
             RomanLiteral(4, "IV"),
             RomanLiteral(1, "I"),
            };

    std::string result;
    while (number > 0) {
        for (const auto &roman_literal : roman_literals) {
            if (roman_literal.get_value() <= number) {
                result.append(roman_literal.get_label());
                number -= roman_literal.get_value();
                break;
            }
        }
    }

    return result;
}
