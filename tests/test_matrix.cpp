#include "matrix.h"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(Matrix, CreateAndFree) {
    auto m = matrix::create_matrix(2, 3);
    EXPECT_DOUBLE_EQ(m.data[1][2], 0.0);
    matrix::free_matrix(m);
}
TEST(Matrix, FromArray) {
    double data[] = {1, 2, 3, 4, 5, 6};
    auto m = matrix::matrix_from_array(data, 2, 3);
    EXPECT_EQ(m.rows, 2); EXPECT_EQ(m.cols, 3);
    EXPECT_DOUBLE_EQ(m.data[1][2], 6);
    data[5] = 0; EXPECT_DOUBLE_EQ(m.data[1][2], 6);
    matrix::free_matrix(m);
}
TEST(Matrix, AddAndMultiply) {
    double x[] = {1, 2, 3, 4}; double y[] = {5, 6, 7, 8};
    auto a = matrix::matrix_from_array(x, 2, 2);
    auto b = matrix::matrix_from_array(y, 2, 2);
    auto sum = matrix::matrix_add(a, b); auto product = matrix::matrix_multiply(a, b);
    EXPECT_DOUBLE_EQ(sum.data[1][1], 12); EXPECT_DOUBLE_EQ(product.data[0][0], 19);
    EXPECT_DOUBLE_EQ(product.data[1][1], 50);
    matrix::free_matrix(a); matrix::free_matrix(b); matrix::free_matrix(sum); matrix::free_matrix(product);
}
TEST(Matrix, InvalidInputs) {
    EXPECT_THROW(matrix::create_matrix(0, 1), std::invalid_argument);
    EXPECT_THROW(matrix::matrix_from_array(nullptr, 2, 2), std::invalid_argument);
    auto a = matrix::create_matrix(2, 3); auto b = matrix::create_matrix(2, 2);
    EXPECT_THROW(matrix::matrix_add(a, b), std::invalid_argument);
    EXPECT_THROW(matrix::matrix_multiply(a, b), std::invalid_argument);
    matrix::free_matrix(a); matrix::free_matrix(b);
    EXPECT_NO_THROW(matrix::free_matrix({nullptr, 0, 0}));
}
TEST(Matrix, RectangularMultiply) {
    const double x[] = {1, 2, 3}; const double y[] = {4, 5, 6};
    auto a = matrix::matrix_from_array(x, 1, 3); auto b = matrix::matrix_from_array(y, 3, 1);
    auto c = matrix::matrix_multiply(a, b); EXPECT_DOUBLE_EQ(c.data[0][0], 32);
    matrix::free_matrix(a); matrix::free_matrix(b); matrix::free_matrix(c);
}
