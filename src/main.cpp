#include <iostream>
#include "mathlib.h"

int main() {
    MathLib::Calculator calc;

    int sum = calc.add(3, 4);
    int product = calc.multiply(3, 4);

    std::cout << "Sum: " << sum << std::endl; // Should output 7
    std::cout << "Product: " << product << std::endl; // Should output 12

    return 0;
}
