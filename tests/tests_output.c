#include "../src/output/output.h"
#include <assert.h>
#include <string.h>

/**
 * @brief Тест для функции erase_file_data.
 * Проверяет, что функция корректно очищает содержимое файла.
 */
void test_erase_file_data() {
  const char *path = "test_file.txt";

  // Создаем файл с некоторыми данными
  FILE *file = fopen(path, "w");
  fprintf(file, "Some data");
  fclose(file);

  // Очищаем файл
  erase_file_data(path);

  // Проверяем, что файл пустой
  FILE *test_file = fopen(path, "r");
  char buffer[100];
  assert(fscanf(test_file, "%s", buffer) == EOF && "Файл не был очищен!");
  fclose(test_file);

  printf("---------------------------------------------------------------------"
         "-----------");

  printf("\nТестирование очищения файла успешно пройдено!\n");

  remove("test_file.txt");
}

/**
 * @brief Тест для функции save_to_file.
 * Проверяет, что функция корректно сохраняет данные в файл.
 */
void test_save_to_file() {
  const char *path = "../results/result.txt";
  const char *data = "Тестовые данные";

  // Очищаем файл перед тестом
  erase_file_data(path);

  // Сохраняем данные в файл
  save_to_file(data);

  // Проверяем, что данные записаны корректно
  FILE *file = fopen(path, "r");
  char buffer[100];
  assert(fscanf(file, "%[^\n]", buffer) != EOF &&
         "Файл пустой или не удалось прочитать данные!");
  assert(strcmp(buffer, "Тестовые данные") == 0 &&
         "Данные в файле не соответствуют ожидаемым!");
  fclose(file);

  printf("Тестирование сохранения данных в файл успешно пройдено!\n");
  printf("---------------------------------------------------------------------"
         "-----------");
}

/**
 * @brief Тест для функции print_data.
 * Проверяет различные сценарии работы функции:
 * - Вывод данных в консоль.
 * - Сохранение данных в файл.
 * - Обработка неверного типа вывода.
 * - Обработка отсутствия данных.
 */
void test_print_data() {
  const char *data = "Тестовые данные";

  // Тестируем вывод в консоль (type_of_output = 1)
  printf("\nОжидаемый вывод: Тестовые данные\n");
  print_data(data, 1);

  // Тестируем запись в файл (type_of_output = 2)
  print_data(data, 2);
  FILE *file = fopen("../results/result.txt", "r");
  char buffer[100];
  assert(fscanf(file, "%[^\n]", buffer) != EOF &&
         "Файл пустой или не удалось прочитать данные!");
  assert(strcmp(buffer, "Тестовые данные") == 0 &&
         "Данные в файле не соответствуют ожидаемым!");
  fclose(file);

  printf("---------------------------------------------------------------------"
         "-----------");

  // Тестируем случай с неверным типом вывода (type_of_output = 3)
  printf("\nОжидаемый вывод: 'Вы ввели неверное число! Попробуйте ещё раз!'\n");
  print_data(data, 3);

  // Тестируем случай с отсутствием данных (data = NULL)
  printf("\nОжидаемый вывод: 'Ошибка: нет данных для вывода!'\n");
  print_data(NULL, 1);

  printf("\nТестирование вывода в консоль успешно пройдено!\n");

  printf("---------------------------------------------------------------------"
         "-----------\n");
}

/**
 * @brief Основная функция для запуска тестов.
 * @return 0, если все тесты прошли успешно.
 */
int main() {
  test_erase_file_data();
  test_save_to_file();
  test_print_data();

  return 0;
}
