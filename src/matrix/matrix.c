#include "matrix.h"

/**
 *@brief Создает матрицу с заданными параметрами
*/
Matrix* create_matrix(int rows, int cols) {
	char flag_error = 0;
	Matrix* matrix = NULL; ///< Указатель на создаваемую матрицу

	if (rows > 0 && cols > 0) { ///< Проверка корректности размеров матрицы
		matrix = (Matrix*)malloc(sizeof(Matrix)); ///< Выделение памяти для структуры Matrix
		if (matrix) {
			matrix->rows = rows;
			matrix->cols = cols;
			matrix->data = (MATRIX_TYPE**)malloc(rows * sizeof(MATRIX_TYPE*)); ///< Выделение памяти для массива указателей на строки

			if (matrix->data) { ///< Проверка успешности выделения памяти под строки
				for (int i = 0; i < rows && flag_error == 0; i++) {
					matrix->data[i] = (MATRIX_TYPE*)malloc(cols * sizeof(MATRIX_TYPE)); ///< Выделение памяти под столбцы каждой строки
					if (!matrix->data[i]) { ///< Проверка успешности выделения памяти
						while (i-- > 0) {
							free(matrix->data[i]); ///< Освобождение уже выделенной памяти в случае ошибки
						}
						free(matrix->data);
						free(matrix);
						matrix = NULL;
						flag_error = 1;
					}
				}
			} else {
				free(matrix); ///< Освобождение памяти в случае ошибки выделения под массив строк
				matrix = NULL;
			}
		}
	}

    return matrix; ///< Возвращение указателя на созданную матрицу или NULL в случае ошибки
}

/**
 * @brief Освобождает память, выделенную под матрицу
 * @param matrix Указатель на матрицу
 */
void free_matrix(Matrix* matrix) {
    if (matrix) {
        for (int i = 0; i < matrix->rows; i++) {
            free(matrix->data[i]); ///< Освобождение памяти для каждой строки
        }
        free(matrix->data); ///< Освобождение памяти массива указателей
        free(matrix); ///< Освобождение памяти структуры Matrix
    }
}

/**
 * @brief Загружает матрицу из текстового файла
 * @param filename Имя файла
 * @return Указатель на загруженную матрицу или NULL в случае ошибки
 */
Matrix* load_matrix_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL; ///< Ошибка открытия файла
    }

    int rows, cols;
    Matrix* matrix = NULL;  // Инициализация переменной матрицы
    int error = 0; // Флаг ошибки

    if (fscanf(file, "%d %d", &rows, &cols) != 2) {
        error = 1; // Ошибка чтения размеров матрицы
    } else {
        matrix = create_matrix(rows, cols);
        if (!matrix) {
            error = 1; // Ошибка создания матрицы
        } else {
            for (int i = 0; i < rows && !error; i++) {
                for (int j = 0; j < cols && !error; j++) {
                    if (fscanf(file, "%d", &matrix->data[i][j]) != 1) {
                        error = 1; // Ошибка чтения данных матрицы
                    }
                }
            }
        }
    }

    if (error) {
        free_matrix(matrix);  // Освобождение памяти в случае ошибки
        fclose(file);  // Закрытие файла
        return NULL;  // Возвращаем NULL в случае ошибки
    }

    fclose(file);  // Закрытие файла
    return matrix;  // Успешно загруженная матрица
}


/**
 * @brief Выводит матрицу в консоль
 * @param matrix Указатель на матрицу
 */
void print_matrix(const Matrix* matrix) {
    if (!matrix) {
        return; ///< Проверка на NULL
    }

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%d ", matrix->data[i][j]); ///< Вывод элемента матрицы
        }
        printf("\n"); ///< Переход на новую строку
    }
}
