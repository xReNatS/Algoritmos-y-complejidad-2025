#include <iostream>
#include <vector>
using namespace std;

using Matrix = vector<vector<int>>;

Matrix add(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix subtract(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

Matrix strassenMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    if (n == 1)
        return {{A[0][0] * B[0][0]}};

    int newSize = n / 2;
    Matrix a11(newSize, vector<int>(newSize));
    Matrix a12(newSize, vector<int>(newSize));
    Matrix a21(newSize, vector<int>(newSize));
    Matrix a22(newSize, vector<int>(newSize));
    Matrix b11(newSize, vector<int>(newSize));
    Matrix b12(newSize, vector<int>(newSize));
    Matrix b21(newSize, vector<int>(newSize));
    Matrix b22(newSize, vector<int>(newSize));

    for (int i = 0; i < newSize; ++i)
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

    Matrix m1 = strassenMultiply(add(a11, a22), add(b11, b22));
    Matrix m2 = strassenMultiply(add(a21, a22), b11);
    Matrix m3 = strassenMultiply(a11, subtract(b12, b22));
    Matrix m4 = strassenMultiply(a22, subtract(b21, b11));
    Matrix m5 = strassenMultiply(add(a11, a12), b22);
    Matrix m6 = strassenMultiply(subtract(a21, a11), add(b11, b12));
    Matrix m7 = strassenMultiply(subtract(a12, a22), add(b21, b22));

    Matrix c11 = add(subtract(add(m1, m4), m5), m7);
    Matrix c12 = add(m3, m5);
    Matrix c21 = add(m2, m4);
    Matrix c22 = add(subtract(add(m1, m3), m2), m6);

    Matrix C(n, vector<int>(n));
    for (int i = 0; i < newSize; ++i)
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = c11[i][j];
            C[i][j + newSize] = c12[i][j];
            C[i + newSize][j] = c21[i][j];
            C[i + newSize][j + newSize] = c22[i][j];
        }

    return C;
}
