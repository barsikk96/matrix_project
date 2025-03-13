#include "matrix/matrix.h"
#include "output/output.h"

int main() {
  Matrix *A = load_matrix_from_file("matrixA.txt");
  Matrix *B = load_matrix_from_file("matrixB.txt");
  Matrix *C = load_matrix_from_file("matrixC.txt");
  Matrix *D = load_matrix_from_file("matrixD.txt");

  Matrix *res = compute_expression(A, B, C, D);

  char *result = converting_to_string(res);
  printf("Выберите вариант вывода результата:\n    1. В консоль.\n    2. В "
         "файл.\n");
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
