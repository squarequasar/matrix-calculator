#include "matrix.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace matrix {
namespace {
void validate(Matrix m) {
    if (!m.data || m.rows <= 0 || m.cols <= 0) throw std::invalid_argument("Invalid matrix");
    for (int i = 0; i < m.rows; ++i) if (!m.data[i]) throw std::invalid_argument("Invalid matrix row");
}
}
Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) throw std::invalid_argument("Invalid dimensions");
    Matrix m{new double*[rows]{}, rows, cols};
    try { for (int i = 0; i < rows; ++i) m.data[i] = new double[cols]{}; }
    catch (...) { free_matrix(m); throw; }
    return m;
}
void free_matrix(Matrix m) {
    if (!m.data) return;
    for (int i = 0; i < m.rows; ++i) delete[] m.data[i];
    delete[] m.data;
}
Matrix matrix_from_array(const double* data, int rows, int cols) {
    if (!data) throw std::invalid_argument("Null array");
    Matrix m = create_matrix(rows, cols);
    for (int i = 0; i < rows; ++i) for (int j = 0; j < cols; ++j)
        m.data[i][j] = data[static_cast<std::size_t>(i) * static_cast<std::size_t>(cols) + static_cast<std::size_t>(j)];
    return m;
}
Matrix matrix_add(Matrix a, Matrix b) {
    validate(a); validate(b);
    if (a.rows != b.rows || a.cols != b.cols) throw std::invalid_argument("Incompatible dimensions");
    Matrix c = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; ++i) for (int j = 0; j < a.cols; ++j) c.data[i][j] = a.data[i][j] + b.data[i][j];
    return c;
}
Matrix matrix_multiply(Matrix a, Matrix b) {
    validate(a); validate(b);
    if (a.cols != b.rows) throw std::invalid_argument("Incompatible dimensions");
    Matrix c = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; ++i) for (int k = 0; k < a.cols; ++k) for (int j = 0; j < b.cols; ++j) c.data[i][j] += a.data[i][k] * b.data[k][j];
    return c;
}
void print_matrix(Matrix m) {
    if (!m.data || m.rows <= 0 || m.cols <= 0) { std::cout << "[Empty matrix]\n"; return; }
    validate(m);
    for (int i = 0; i < m.rows; ++i) {
        std::cout << "[";
        for (int j = 0; j < m.cols; ++j) std::cout << std::setw(8) << std::fixed << std::setprecision(2) << m.data[i][j];
        std::cout << " ]\n";
    }
}
}
