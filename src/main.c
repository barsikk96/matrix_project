#include "matrix/matrix.h"
#include "output/output.h"

Matrix* compute_expression(const Matrix* A, const Matrix* B, const Matrix* C, const Matrix* D);

int main() {
    Matrix* A = load_matrix_from_file("matrixA.txt");
    Matrix* B = load_matrix_from_file("matrixB.txt");
    Matrix* C = load_matrix_from_file("matrixC.txt");
    Matrix* D = load_matrix_from_file("matrixD.txt");

    Matrix* res = compute_expression(A, B, C, D);

    char* result = converting_to_string(res);
    printf("Выберите вариант вывода результата:\n    1. В консоль.\n    2. В файл.\n");
    int type_of_output;
    scanf("%d", &type_of_output);
    print_data(result, type_of_output);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(D);
    free_matrix(res);
    free(result);
    return 0;
}

/* @brief Решение примера (A^T − B + C) × D
 * @param A Матрица А
 * @param B Матрица B
 * @param C Матрица C
 * @param D Матрица D
 * @return Указатель на результирующую матрицу
 */
Matrix* compute_expression(const Matrix* A, const Matrix* B, const Matrix* C, const Matrix* D) {
    Matrix* temp1 = transpose_matrix(A);
    Matrix* temp2 = subtract_matrices(temp1, B);
    Matrix* temp3 = add_matrices(temp2, C);
    Matrix* temp4 = multiply_matrices(temp3, D);
    Matrix* result = copy_matrix(temp4);

    free_matrix(temp1);
    free_matrix(temp2);
    free_matrix(temp3);
    free_matrix(temp4);

    return result;
}
