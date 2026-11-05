#include "matrix.h"
#include <exception>
#include <iostream>

int main() {
    try {
        const double values[] = {1, 2, 3, 4};
        matrix::Matrix a = matrix::matrix_from_array(values, 2, 2);
        matrix::print_matrix(a);
        matrix::free_matrix(a);
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
    return 0;
}
