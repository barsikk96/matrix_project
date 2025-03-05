CC = gcc

CFLAGS = -Wall -Wextra -g -std=c11 -DDEBUG -I$(SRC_DIR) -I$(MATRIX_DIR) -I$(OUTPUT_DIR) -fsanitize=address

SRC_DIR = src
MATRIX_DIR = $(SRC_DIR)/matrix
OUTPUT_DIR = $(SRC_DIR)/output
TESTS_DIR = tests

OBJ = $(SRC_DIR)/main.o $(MATRIX_DIR)/matrix.o $(OUTPUT_DIR)/output.o
TEST_OBJ = $(TESTS_DIR)/tests_matrix.o $(MATRIX_DIR)/matrix.o $(OUTPUT_DIR)/output.o

TARGET = matrix_main
TEST_TARGET = tests_run

SRCS = $(SRC_DIR)/main.c $(MATRIX_DIR)/matrix.c $(OUTPUT_DIR)/output.c $(TESTS_DIR)/tests_matrix.c

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)
$(TEST_TARGET): $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o $(TEST_TARGET)

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(MATRIX_DIR)%.o: $(MATRIX_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(OUTPUT_DIR)%.o: $(OUTPUT_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(TESTS_DIR)%.o: $(TESTS_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

cppcheck:
	cppcheck --enable=all --suppress=missingInclude --suppress=missingIncludeSystem --platform=unix64 $(SRCS)

check: cppcheck
	@echo "Проверка cppcheck завершена."

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET)

rebuild: clean $(TARGET) $(TEST_TARGET)
