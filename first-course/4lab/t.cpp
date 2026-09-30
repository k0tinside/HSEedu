#include <iostream>

int main() {
    // двумерный массив
    int row, cols;
    float** matr = new float*[row];
    for (int i = 0; i < row; ++i) {
        *(matr + i) = new float[cols];
    }

    // трехмерный массив
    int n, m, k;
    int*** cube = new int**[n];
    for (int i = 0; i < n; ++i) {
        *(cube + i) = new int*[m];
        for (int j = 0; j < m; ++j) {
            *(*(cube + i) + j) = new int[k];
        }
    }

    return 0;
}