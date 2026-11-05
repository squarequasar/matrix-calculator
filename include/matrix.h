#pragma once

namespace matrix {
/// Матрица владеет выделенной памятью; освободить через free_matrix.
struct Matrix { double** data; int rows; int cols; };
/// @brief Создать нулевую матрицу. @param rows Строки. @param cols Столбцы. @return Матрица. @throw std::invalid_argument При неверном размере.
Matrix create_matrix(int rows, int cols);
/// @brief Освободить память матрицы. @param m Матрица; повторное освобождение запрещено.
void free_matrix(Matrix m);
/// @brief Создать матрицу из массива. @param data Массив. @param rows Строки. @param cols Столбцы. @return Матрица. @throw std::invalid_argument При ошибке ввода.
Matrix matrix_from_array(const double* data, int rows, int cols);
/// @brief Сложить матрицы. @param a Первый операнд. @param b Второй операнд. @return Сумма. @throw std::invalid_argument При несовместимых размерах.
Matrix matrix_add(Matrix a, Matrix b);
/// @brief Умножить матрицы. @param a Первый операнд. @param b Второй операнд. @return Произведение. @throw std::invalid_argument При несовместимых размерах.
Matrix matrix_multiply(Matrix a, Matrix b);
/// @brief Вывести матрицу. @param m Матрица.
void print_matrix(Matrix m);
}
