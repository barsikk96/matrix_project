#ifndef TESTS_MAIN_H
#define TESTS_MAIN_H
#include "../src/matrix/matrix.h"
#include "../src/output/output.h"
#include <assert.h>
#include <time.h>
#include <stdlib.h>

Matrix *create_matrix_with_values(int rows, int cols, MATRIX_TYPE values[]);

void test_compute_expression();

void test_matrix_create_performance();

#endif
