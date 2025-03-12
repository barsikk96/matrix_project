#include "matrix/matrix.h"
#include "output/output.h"

int main() {
    Matrix* A = load_matrix_from_file("matrixA.txt");
    Matrix* B = load_matrix_from_file("matrixB.txt");
    Matrix* C = create_matrix(2, 2);

    char* result = converting_to_string(A);
    printf("Выберите вариант вывода результата:\n    1. В консоль.\n    2. В файл.\n");
    int type_of_output;
    scanf("%d", &type_of_output);
    print_data(result, type_of_output);

    free_matrix(A);
    free_matrix(B);
	free_matrix(C);
    free(result);
    return 0;
}
