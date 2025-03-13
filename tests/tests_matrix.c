#include "../src/matrix/matrix.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>

void test_create_delete_matrix() {
  Matrix *matrix = create_matrix(3, 3);
  assert(matrix != NULL && "Ошибка при создании матрицы");
  assert(matrix->rows == 3 && "Неверное количество строк");
  assert(matrix->cols == 3 && "Неверное количество столбцов");
  free_matrix(matrix);
}

void test_add_matrices() {
  Matrix *A = create_matrix(2, 2);
  Matrix *B = create_matrix(2, 2);

  A->data[0][0] = 1;
  A->data[0][1] = 2;
  A->data[1][0] = 3;
  A->data[1][1] = 4;
  B->data[0][0] = 5;
  B->data[0][1] = 6;
  B->data[1][0] = 7;
  B->data[1][1] = 8;

  Matrix *result = add_matrices(A, B);
  assert(result != NULL && "Ошибка при сложении матриц");
  assert(result->data[0][0] == 6 && "Ошибка при сложении матриц");
  assert(result->data[0][1] == 8 && "Ошибка при сложении матриц");
  assert(result->data[1][0] == 10 && "Ошибка при сложении матриц");
  assert(result->data[1][1] == 12 && "Ошибка при сложении матриц");

  free_matrix(A);
  free_matrix(B);
  free_matrix(result);
}

void test_subtract_matrices() {
  Matrix *A = create_matrix(2, 2);
  Matrix *B = create_matrix(2, 2);

  A->data[0][0] = 5;
  A->data[0][1] = 6;
  A->data[1][0] = 7;
  A->data[1][1] = 8;
  B->data[0][0] = 1;
  B->data[0][1] = 2;
  B->data[1][0] = 3;
  B->data[1][1] = 4;

  Matrix *result = subtract_matrices(A, B);
  assert(result != NULL && "Ошибка при вычитании матриц");
  assert(result->data[0][0] == 4 && "Ошибка при вычитании матриц");
  assert(result->data[0][1] == 4 && "Ошибка при вычитании матриц");
  assert(result->data[1][0] == 4 && "Ошибка при вычитании матриц");
  assert(result->data[1][1] == 4 && "Ошибка при вычитании матриц");

  free_matrix(A);
  free_matrix(B);
  free_matrix(result);
}

void test_multiply_matrices() {
  Matrix *A = create_matrix(2, 3);
  Matrix *B = create_matrix(3, 2);

  A->data[0][0] = 1;
  A->data[0][1] = 2;
  A->data[0][2] = 3;
  A->data[1][0] = 4;
  A->data[1][1] = 5;
  A->data[1][2] = 6;

  B->data[0][0] = 7;
  B->data[0][1] = 8;
  B->data[1][0] = 9;
  B->data[1][1] = 10;
  B->data[2][0] = 11;
  B->data[2][1] = 12;

  Matrix *result = multiply_matrices(A, B);
  assert(result != NULL && "Ошибка при умножении матриц");
  assert(result->data[0][0] == 58 && "Ошибка при умножении матриц");
  assert(result->data[0][1] == 64 && "Ошибка при умножении матриц");
  assert(result->data[1][0] == 139 && "Ошибка при умножении матриц");
  assert(result->data[1][1] == 154 && "Ошибка при умножении матриц");

  free_matrix(A);
  free_matrix(B);
  free_matrix(result);
}

void test_transpose_matrix() {
  Matrix *A = create_matrix(2, 3);
  A->data[0][0] = 1;
  A->data[0][1] = 2;
  A->data[0][2] = 3;
  A->data[1][0] = 4;
  A->data[1][1] = 5;
  A->data[1][2] = 6;

  Matrix *result = transpose_matrix(A);
  assert(result != NULL && "Ошибка при транспонировании матрицы");
  assert(result->rows == 3 &&
         "Неверное количество строк после транспонирования");
  assert(result->cols == 2 &&
         "Неверное количество столбцов после транспонирования");
  assert(result->data[0][0] == 1 && "Ошибка при транспонировании матрицы");
  assert(result->data[1][0] == 2 && "Ошибка при транспонировании матрицы");
  assert(result->data[2][0] == 3 && "Ошибка при транспонировании матрицы");

  free_matrix(A);
  free_matrix(result);
}

void test_determinant() {
  Matrix *A = create_matrix(2, 2);
  A->data[0][0] = 1;
  A->data[0][1] = 2;
  A->data[1][0] = 3;
  A->data[1][1] = 4;

  MATRIX_TYPE result = determinant(A);
  assert(result == -2 && "Неверное значение детерминанта");

  free_matrix(A);
}

void test_copy_matrix() {
  Matrix *A = create_matrix(2, 2);
  A->data[0][0] = 1;
  A->data[0][1] = 2;
  A->data[1][0] = 3;
  A->data[1][1] = 4;

  Matrix *result = copy_matrix(A);
  assert(result != NULL && "Ошибка при копировании матрицы");
  assert(result->data[0][0] == 1 && "Ошибка при копировании матрицы");
  assert(result->data[0][1] == 2 && "Ошибка при копировании матрицы");
  assert(result->data[1][0] == 3 && "Ошибка при копировании матрицы");
  assert(result->data[1][1] == 4 && "Ошибка при копировании матрицы");

  free_matrix(A);
  free_matrix(result);
}

void test_converting_to_string() {
  Matrix *A = create_matrix(2, 2);
  A->data[0][0] = 1;
  A->data[0][1] = 2;
  A->data[1][0] = 3;
  A->data[1][1] = 4;

  char *result = converting_to_string(A);
  assert(result != NULL && "Ошибка при конвертации матрицы в строку");

  // Проверяем, что строка содержит ожидаемые числа и символы
  assert(strstr(result, "1") != NULL && "Не найдено число 1");
  assert(strstr(result, "2") != NULL && "Не найдено число 2");
  assert(strstr(result, "3") != NULL && "Не найдено число 3");
  assert(strstr(result, "4") != NULL && "Не найдено число 4");
  assert(strstr(result, "\n") != NULL && "Не найден символ новой строки");

  free(result);
  free_matrix(A);
}

int main() {
  printf("Тестирование создания матрицы..\n");
  sleep(1);
  test_create_delete_matrix();
  printf("Тестирование сложения матриц..\n");
  sleep(1);
  test_add_matrices();
  printf("Тестирование вычитания матриц..\n");
  sleep(1);
  test_subtract_matrices();
  printf("Тестирование умножения матриц..\n");
  sleep(1);
  test_multiply_matrices();
  printf("Тестирование транспонирования матрицы..\n");
  sleep(1);
  test_transpose_matrix();
  printf("Тестирование вычисления детерминанта матрицы..\n");
  sleep(1);
  test_determinant();
  printf("Тестирование копирования матрицы..\n");
  sleep(1);
  test_copy_matrix();
  printf("Тестирование конвертации матрицы в строку..\n");
  sleep(1);
  test_converting_to_string();

  printf("Тестирование фукнций модуля matrix прошло успешно!\n");
  return 0;
}
