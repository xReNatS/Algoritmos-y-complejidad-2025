//referencia: el siguiente codigo fue extraido a traves de prompts de chatGPT

#include <iostream>
#include "strassen.hpp"
using namespace std;

using Matrix = vector<vector<int>>;

const int STRASSEN_THRESHOLD = 64; // Cambia este valor si quieres ajustar el punto de corte

// Suma de matrices (C = A + B)
void add(const Matrix& A, const Matrix& B, Matrix& C) {
    int n = A.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
}

// Resta de matrices (C = A - B)
void subtract(const Matrix& A, const Matrix& B, Matrix& C) {
    int n = A.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
}

// Multiplicación estándar básica
void multiplyBasic(const Matrix& A, const Matrix& B, Matrix& C) {
    int n = A.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];
        }
}

Matrix strassenMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));

    if (n <= STRASSEN_THRESHOLD) {
        multiplyBasic(A, B, C);
        return C;
    }

    int newSize = n / 2;
    Matrix a11(newSize, vector<int>(newSize));
    Matrix a12(newSize, vector<int>(newSize));
    Matrix a21(newSize, vector<int>(newSize));
    Matrix a22(newSize, vector<int>(newSize));
    Matrix b11(newSize, vector<int>(newSize));
    Matrix b12(newSize, vector<int>(newSize));
    Matrix b21(newSize, vector<int>(newSize));
    Matrix b22(newSize, vector<int>(newSize));

    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + newSize];
            a21[i][j] = A[i + newSize][j];
            a22[i][j] = A[i + newSize][j + newSize];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + newSize];
            b21[i][j] = B[i + newSize][j];
            b22[i][j] = B[i + newSize][j + newSize];
        }
    }

    Matrix m1(newSize, vector<int>(newSize));
    Matrix m2(newSize, vector<int>(newSize));
    Matrix m3(newSize, vector<int>(newSize));
    Matrix m4(newSize, vector<int>(newSize));
    Matrix m5(newSize, vector<int>(newSize));
    Matrix m6(newSize, vector<int>(newSize));
    Matrix m7(newSize, vector<int>(newSize));

    Matrix AResult(newSize, vector<int>(newSize));
    Matrix BResult(newSize, vector<int>(newSize));

    add(a11, a22, AResult); // AResult = a11 + a22
    add(b11, b22, BResult); // BResult = b11 + b22
    m1 = strassenMultiply(AResult, BResult);

    add(a21, a22, AResult);
    m2 = strassenMultiply(AResult, b11);

    subtract(b12, b22, BResult);
    m3 = strassenMultiply(a11, BResult);

    subtract(b21, b11, BResult);
    m4 = strassenMultiply(a22, BResult);

    add(a11, a12, AResult);
    m5 = strassenMultiply(AResult, b22);

    subtract(a21, a11, AResult);
    add(b11, b12, BResult);
    m6 = strassenMultiply(AResult, BResult);

    subtract(a12, a22, AResult);
    add(b21, b22, BResult);
    m7 = strassenMultiply(AResult, BResult);

    Matrix c11(newSize, vector<int>(newSize));
    Matrix c12(newSize, vector<int>(newSize));
    Matrix c21(newSize, vector<int>(newSize));
    Matrix c22(newSize, vector<int>(newSize));

    add(m1, m4, AResult);
    subtract(AResult, m5, BResult);
    add(BResult, m7, c11);

    add(m3, m5, c12);

    add(m2, m4, c21);

    add(m1, m3, AResult);
    subtract(AResult, m2, BResult);
    add(BResult, m6, c22);

    for (int i = 0; i < newSize; ++i)
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = c11[i][j];
            C[i][j + newSize] = c12[i][j];
            C[i + newSize][j] = c21[i][j];
            C[i + newSize][j + newSize] = c22[i][j];
        }

    return C;
}