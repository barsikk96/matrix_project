#include "/home/ethelay/homework/matrix_project/src/matrix/matrix.h"

int main() {
    Matrix* A = load_matrix_from_file("/home/ethelay/homework/matrix_project/src/matrix/matrix_list.txt");
    print_matrix(A);
    free_matrix(A);
    return 0;
}
