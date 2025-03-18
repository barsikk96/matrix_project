#include "tests_main.h"

/**
 * @brief Создает матрицу с заданными значениями
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @param values Массив значений для инициализации матрицы
 * @return Указатель на созданную матрицу или NULL в случае ошибки
 */
Matrix *create_matrix_with_values(int rows, int cols, MATRIX_TYPE values[]) {
  Matrix *matrix = create_matrix(rows, cols);
  if (matrix) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        matrix->data[i][j] = values[i * cols + j];
      }
    }
  }
  return matrix;
}

/**
 * @brief Тестирует функцию compute_expression
 * @details Создает тестовые матрицы, вычисляет выражение и проверяет результат.
 * В случае ошибки выводит сообщение и завершает программу.
 */
void test_compute_expression() {
  // Создаем тестовые матрицы
  MATRIX_TYPE A_values[] = {1, 2, 3, 4};
  MATRIX_TYPE B_values[] = {5, 6, 7, 8};
  MATRIX_TYPE C_values[] = {9, 10, 11, 12};
  MATRIX_TYPE D_values[] = {13, 14, 15, 16};

  Matrix *A = create_matrix_with_values(2, 2, A_values);
  Matrix *B = create_matrix_with_values(2, 2, B_values);
  Matrix *C = create_matrix_with_values(2, 2, C_values);
  Matrix *D = create_matrix_with_values(2, 2, D_values);

  // Проверяем, что матрицы созданы успешно
  assert(A != NULL && "Ошибка: не удалось создать матрицу\n");
  assert(B != NULL && "Ошибка: не удалось создать матрицу\n");
  assert(C != NULL && "Ошибка: не удалось создать матрицу\n");
  assert(D != NULL && "Ошибка: не удалось создать матрицу\n");

  // Вычисляем результат выражения
  Matrix *result = compute_expression(A, B, C, D);

  // Проверяем, что результат вычислен успешно
  assert(result != NULL && "Ошибка: не удалось вычислить выражение\n");

  // Ожидаемый результат после выполнения операций:
  // temp1 = A^T = [1, 3; 2, 4]
  // temp2 = temp1 - B = [1-5, 3-6; 2-7, 4-8] = [-4, -3; -5, -4]
  // temp3 = temp2 + C = [-4+9, -4+11; -4+10, -4+12] = [5, 7; 6, 8]
  // temp4 = temp3 * D = [5*13 + 7*15, 5*14 + 7*16; 6*13 + 8*15, 6*14 + 8*16] =
  // [170, 182; 198, 212] result = temp4 = [170, 182; 198, 212]

  MATRIX_TYPE expected_values[] = {170, 182, 198, 212};
  Matrix *expected = create_matrix_with_values(2, 2, expected_values);

  // Проверяем, что результат совпадает с ожидаемым
  assert(expected != NULL && "Ошибка: не удалось создать матрицу\n");
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->cols; j++) {
      assert(result->data[i][j] == expected->data[i][j] &&
             "Ошибка: результат не совпадает с ожидаемым значением\n");
    }
  }

  // Освобождаем память
  free_matrix(A);
  free_matrix(B);
  free_matrix(C);
  free_matrix(D);
  free_matrix(result);
  free_matrix(expected);

  printf("Тест пройден успешно!\n");
}

// Функция для измерения времени выполнения
void test_matrix_create_performance() {
  char filename[] = {"matrix_test.txt"};
  char test_values[] = {"2 2\n-2147483648 2147483647\n0 1\n"};
  save_to_file(test_values, filename);

  clock_t start, end;
  double cpu_time_used;

  // Создаем матрицу с граничными значениями
  start = clock();
  Matrix *matrix = load_matrix_from_file(filename); // Матрица 2x2
  end = clock();

  if (matrix) {
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время создания файла: %f seconds\n", cpu_time_used);
    free_matrix(matrix); // Освобождаем память после теста
  } else {
    printf("Ошибка считывания значений матрицы\n");
    assert(0 && "Ошибка при создании матрицы");
  }

  remove(filename);
}
