#pragma once
#include "matrix.hpp"

using Matrix = std::vector<std::vector<int>>;

Matrix naiveMultiply(const Matrix& A, const Matrix& B);
