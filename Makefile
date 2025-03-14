CC = gcc

CFLAGS = -Wall -Wextra -g -std=c11 -DDEBUG -I$(SRC_DIR) -I$(MATRIX_DIR) -I$(OUTPUT_DIR) -I$(TESTS_DIR) -fsanitize=address

SRC_DIR = src
MATRIX_DIR = $(SRC_DIR)/matrix
OUTPUT_DIR = $(SRC_DIR)/output
TESTS_DIR = tests

OBJ = $(SRC_DIR)/main.o $(MATRIX_DIR)/matrix.o $(OUTPUT_DIR)/output.o
TEST_MATRIX_OBJ = $(TESTS_DIR)/tests_matrix.o $(MATRIX_DIR)/matrix.o $(OUTPUT_DIR)/output.o
TEST_OUTPUT_OBJ = $(TESTS_DIR)/tests_output.o $(MATRIX_DIR)/matrix.o $(OUTPUT_DIR)/output.o
TEST_MAIN_OBJ = $(TESTS_DIR)/tests_main.o $(MATRIX_DIR)/matrix.o $(OUTPUT_DIR)/output.o

BIN_DIR = build
TARGET_MAIN = $(BIN_DIR)/matrix_main
TEST_MATRIX_TARGET = $(BIN_DIR)/tests_matrix
TEST_OUTPUT_TARGET = $(BIN_DIR)/tests_output
TEST_MAIN_TARGET = $(BIN_DIR)/tests_main

SRCS = $(SRC_DIR)/main.c $(MATRIX_DIR)/matrix.c $(OUTPUT_DIR)/output.c $(TESTS_DIR)/tests_matrix.c $(TESTS_DIR)/tests_output.c $(TESTS_DIR)/tests_main.c

$(TARGET_MAIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET_MAIN)
$(TEST_MATRIX_TARGET): $(TEST_MATRIX_OBJ)
	$(CC) $(CFLAGS) $(TEST_MATRIX_OBJ) -o $(TEST_MATRIX_TARGET)
$(TEST_OUTPUT_TARGET): $(TEST_OUTPUT_OBJ)
	$(CC) $(CFLAGS) $(TEST_OUTPUT_OBJ) -o $(TEST_OUTPUT_TARGET)
$(TEST_MAIN_TARGET): $(TEST_MAIN_OBJ)
	$(CC) $(CFLAGS) $(TEST_MAIN_OBJ) -o $(TEST_MAIN_TARGET)


$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(MATRIX_DIR)%.o: $(MATRIX_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(OUTPUT_DIR)%.o: $(OUTPUT_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(TESTS_DIR)%.o: $(TESTS_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

test_cunit:
	gcc -o test_runner tests/test_runner.c -lcunit

cppcheck:
	cppcheck --enable=all --suppress=missingInclude --suppress=missingIncludeSystem --platform=unix64 $(SRCS)

lint: cppcheck
	@echo "Проверка cppcheck завершена."

format:
	clang-format -style=LLVM -i src/*.c src/matrix/*.h src/matrix/*.c src/output/*.h src/output/*.c tests/*.c include/*.h

clean:
	rm -f $(OBJ) $(TEST_MATRIX_OBJ) $(TEST_OUTPUT_OBJ) $(TEST_MAIN_OBJ) $(TARGET_MAIN) $(TEST_MATRIX_TARGET) $(TEST_OUTPUT_TARGET) $(TEST_MAIN_TARGET)

rebuild: clean $(TARGET_MAIN) $(TEST_MATRIX_TARGET) $(TEST_OUTPUT_TARGET) $(TEST_MAIN_TARGET)
