//referencia: el siguiente codigo fue extraido a traves de prompts de chatGPT

#include "naive.hpp"

Matrix naiveMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, std::vector<int>(n, 0)); // Inicializamos la matriz resultado con ceros

    for (int i = 0; i < n; ++i)
        for (int k = 0; k < n; ++k)
            for (int j = 0; j < n; ++j)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}