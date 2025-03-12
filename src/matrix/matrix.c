#include "matrix.h"

/**
 * @brief Создает матрицу и инициализирует ее нулями
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Указатель на созданную матрицу
 */
Matrix* create_matrix(int rows, int cols) {
    Matrix* matrix = NULL; ///< Указатель на создаваемую матрицу

    if (rows > 0 && cols > 0) { ///< Проверка корректности размеров матрицы
        char flag_error = 0;
        matrix = (Matrix*)malloc(sizeof(Matrix)); ///< Выделение памяти для структуры Matrix
        if (matrix) {
            matrix->rows = rows;
            matrix->cols = cols; 
            matrix->data = (MATRIX_TYPE**)calloc(rows, rows * sizeof(MATRIX_TYPE*)); ///< Выделение памяти для массива указателей на строки

            if (matrix->data) { ///< Проверка успешности выделения памяти под строки
                for (size_t i = 0; i < (size_t)rows && flag_error == 0; i++) {
                    matrix->data[i] = (MATRIX_TYPE*)calloc(cols, cols * sizeof(MATRIX_TYPE)); ///< Выделение памяти под столбцы каждой строки
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
        for (size_t i = 0; i < (size_t)matrix->rows; i++) {
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
            for (size_t i = 0; i < (size_t)rows && !error; i++) {
                for (size_t j = 0; j < (size_t)cols && !error; j++) {
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
 * @brief Копирует матрицу
 * @param source Указатель на исходную матрицу
 * @return Указатель на копию матрицы или NULL в случае ошибки
 */
Matrix* copy_matrix(const Matrix* source) {
    Matrix* copy = NULL; // Инициализация указателя
    if (source) { // Проверка входных данных
        copy = create_matrix(source->rows, source->cols);
        if (copy) { // Проверка успешного выделения памяти
            for (size_t i = 0; i < (size_t)source->rows; i++) {
                for (size_t j = 0; j < (size_t)source->cols; j++) {
                    copy->data[i][j] = source->data[i][j]; // Копирование данных
                }
            }
        }
    }
    return copy;
}

/**
 * @brief Складывает две матрицы
 * @param A Указатель на первую матрицу
 * @param B Указатель на вторую матрицу
 * @return Указатель на новую матрицу — результат сложения, либо NULL в случае ошибки
 */
Matrix* add_matrices(const Matrix* A, const Matrix* B) {
    Matrix* result = NULL; ///< Инициализация указателя
    if (A && B && A->rows == B->rows && A->cols == B->cols) { // Проверка корректности
        result = create_matrix(A->rows, A->cols);
        if (result) { ///< Проверка успешного выделения памяти
            for (size_t i = 0; i < (size_t)A->rows; i++) {
                for (size_t j = 0; j < (size_t)A->cols; j++) {
                    result->data[i][j] = A->data[i][j] + B->data[i][j]; ///< Сложение элементов
                }
            }
        }
    }
    return result;
}

/**
 * @brief Вычитает одну матрицу из другой
 * @param A Указатель на первую матрицу
 * @param B Указатель на вторую матрицу
 * @return Указатель на новую матрицу — результат вычитания, либо NULL в случае ошибки
 */
Matrix* subtract_matrices(const Matrix* A, const Matrix* B) {
    Matrix* result = NULL; ///< Инициализация указателя
    if (A && B && A->rows == B->rows && A->cols == B->cols) { ///< Проверка корректности
        result = create_matrix(A->rows, A->cols);
        if (result) { ///< Проверка успешного выделения памяти
            for (size_t i = 0; i < (size_t)A->rows; i++) {
                for (size_t j = 0; j < (size_t)A->cols; j++) {
                    result->data[i][j] = A->data[i][j] - B->data[i][j]; ///< Вычитание элементов
                }
            }
        }
    }
    return result;
}

/**
 * @brief Умножает две матрицы
 * @param A Указатель на первую матрицу
 * @param B Указатель на вторую матрицу
 * @return Указатель на новую матрицу — результат умножения, либо NULL в случае ошибки
 */
Matrix* multiply_matrices(const Matrix* A, const Matrix* B) {
    Matrix* result = NULL; // Инициализация указателя
    if (A && B && A->cols == B->rows) { // Проверка корректности
        result = create_matrix(A->rows, B->cols);
        if (result) { // Проверка успешного выделения памяти
            for (size_t i = 0; i < (size_t)A->rows; i++) {
                for (size_t j = 0; j < (size_t)B->cols; j++) {
                    result->data[i][j] = 0; // Обнуление перед вычислением
                    for (size_t k = 0; k < (size_t)A->cols; k++) {
                        result->data[i][j] += A->data[i][k] * B->data[k][j]; // Умножение
                    }
                }
            }
        }
    }
    return result;
}

/**
 * @brief Транспонирует матрицу
 * @param matrix Указатель на матрицу
 * @return Указатель на новую транспонированную матрицу, либо NULL в случае ошибки
 */
Matrix* transpose_matrix(const Matrix* matrix) {
    Matrix* transposed = NULL; // Инициализация указателя
    if (matrix) { // Проверка корректности
        transposed = create_matrix(matrix->cols, matrix->rows);
        if (transposed) { // Проверка успешного выделения памяти
            for (size_t i = 0; i < (size_t)matrix->rows; i++) {
                for (size_t j = 0; j < (size_t)matrix->cols; j++) {
                    transposed->data[j][i] = matrix->data[i][j]; // Транспонирование
                }
            }
        }
    }
    return transposed;
}

/**
 * @brief Вычисляет детерминант квадратной матрицы
 * @param matrix Указатель на квадратную матрицу
 * @return Значение детерминанта матрицы
 */
MATRIX_TYPE determinant(const Matrix* matrix) {
    MATRIX_TYPE det = 0; // Инициализация детерминанта
    if (matrix && matrix->rows == matrix->cols) { // Проверка корректности
        if (matrix->rows == 1) {
            det = matrix->data[0][0]; // Детерминант 1x1
        } else {
            int sign = 1; // Переменная для чередования знака
            for (size_t k = 0; k < (size_t)matrix->cols; k++) {
                Matrix* minor = create_matrix(matrix->rows - 1, matrix->cols - 1);
                if (minor) {
                    for (size_t i = 1; i < (size_t)matrix->rows; i++) {
                        int col_index = 0;
                        for (size_t j = 0; j < (size_t)matrix->cols; j++) {
                            if (j == k) continue;
                            minor->data[i - 1][col_index++] = matrix->data[i][j];
                        }
                    }
                    det += sign * matrix->data[0][k] * determinant(minor); // Вычисление миноров
                    sign = -sign; // Изменение знака
                    free_matrix(minor); // Освобождение памяти
                }
            }
        }
    }
    return det;
}

char* converting_to_string(Matrix* matrix) {
    char* result = NULL;
    if(matrix) {
        char error_flag = 0;
        size_t max_element_size = 12;
        size_t result_size = matrix->rows * matrix->cols * max_element_size + 1; ///< 12 байт на число (с запасом)
        result = (char*)calloc(1, result_size);

        if(result) {
            char* current_pos = result;

            for(size_t i = 0; i < (size_t)matrix->rows && error_flag == 0; i++) {
                for(size_t j = 0; j < (size_t)matrix->cols && error_flag == 0; j++) {
                    int written = snprintf(current_pos, result_size - (current_pos - result), "%d ", matrix->data[i][j]);

                    if (written < 0 || written >= (int)(result_size - (current_pos - result))) {
                        free(result);
                        error_flag = 1; // Переполнение буфера
                    }

                    if(error_flag == 0) current_pos += written;
                }
                if(error_flag == 0) *(current_pos - 1) = '\n';;
            }
            if(error_flag == 0) *(current_pos - 1) = '\0';
        }
    }

    return result;
}
