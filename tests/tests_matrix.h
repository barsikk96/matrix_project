#ifndef TESTS_MATRIX_H
#define TESTS_MATRIX_H

#include "../src/matrix/matrix.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>

void test_create_delete_matrix();

void test_add_matrices();

void test_subtract_matrices();

void test_multiply_matrices();

void test_transpose_matrix();

void test_determinant();

void test_copy_matrix();

void test_converting_to_string();

#endif
