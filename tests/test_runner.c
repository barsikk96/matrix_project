#include "/usr/include/CUnit/Basic.h"
#include "/usr/include/CUnit/CUnit.h"
#include "tests_main.h"
#include "tests_matrix.h"
#include "tests_output.h"

int main() {
  /* Инициализация CUnit
   */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* Создание тестового набора для matrix
   */
  CU_pSuite suite_matrix = CU_add_suite("matrix_test", 0, 0);
  if (NULL == suite_matrix) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* Создание тестового набора для output
   */
  CU_pSuite suite_output = CU_add_suite("output_test", 0, 0);
  if (NULL == suite_output) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* Создание тестового набора для main
   */
  CU_pSuite suite_main = CU_add_suite("main_test", 0, 0);
  if (NULL == suite_main) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Тест test_compute_expression(main)
   */
  if (NULL == CU_add_test(suite_main,
                          "Тест решения выражения:", test_compute_expression)) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* Тест test_matrix_create_performance(main)
   */
  if (NULL == CU_add_test(suite_main,
                          "Тест создания матрицы c граничными значениями:",
                          test_matrix_create_performance)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Тест test_add_matrices(matrix)
   */
  if (NULL ==
      CU_add_test(suite_matrix, "Тест сложения матриц:", test_add_matrices)) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* Тест test_subtract_matrices(matrix)
   */
  if (NULL == CU_add_test(suite_matrix,
                          "Тест вычитания матриц:", test_subtract_matrices)) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* Тест test_multiply_matrices(matrix)
   */
  if (NULL == CU_add_test(suite_matrix,
                          "Тест умножения матриц:", test_multiply_matrices)) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* Тест test_transpose_matrix(matrix)
   */
  if (NULL == CU_add_test(suite_matrix, "Тест транспонирования матрицы:",
                          test_transpose_matrix)) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* Тест test_determinant(matrix)
   */
  if (NULL == CU_add_test(suite_matrix,
                          "Тест вычисления детерминанта:", test_determinant)) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* Тест test_copy_matrix(matrix)
   */
  if (NULL == CU_add_test(suite_matrix,
                          "Тест копирования матрицы:", test_copy_matrix)) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* Тест test_converting_to_string(matrix)
   */
  if (NULL == CU_add_test(suite_matrix, "Тест конвертации в строку:",
                          test_converting_to_string)) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* Тест test_create_delete_matrix(matrix)
   */
  if (NULL == CU_add_test(suite_matrix, "Тест создания/удаления матрицы:",
                          test_create_delete_matrix)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Тест test_erase_file_data(output)
   */
  if (NULL ==
      CU_add_test(suite_output, "Тест очищения файла", test_erase_file_data)) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* Тест test_save_to_file(output)
   */
  if (NULL == CU_add_test(suite_output, "Тест сохранения данных в файл",
                          test_save_to_file)) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* Тест test_print_data(output)
   */
  if (NULL == CU_add_test(suite_output, "Тест вывода/сохранения в файл данных",
                          test_print_data)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Запуск всех тестов
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
