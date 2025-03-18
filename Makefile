CC = gcc

CFLAGS = -Wall -Wextra -g -std=c11 -DDEBUG -I$(SRC_DIR) -I$(MATRIX_DIR) -I$(OUTPUT_DIR) -I$(TESTS_DIR) -fsanitize=address

SRC_DIR = src
MATRIX_DIR = $(SRC_DIR)/matrix
OUTPUT_DIR = $(SRC_DIR)/output
TESTS_DIR = tests

OBJ = $(SRC_DIR)/main.o $(MATRIX_DIR)/matrix.o $(OUTPUT_DIR)/output.o
TEST_OBJ = $(TESTS_DIR)/tests_matrix.o $(TESTS_DIR)/tests_output.o $(TESTS_DIR)/tests_main.o $(MATRIX_DIR)/matrix.o $(OUTPUT_DIR)/output.o

BIN_DIR = build
TARGET_MAIN = $(BIN_DIR)/matrix_main
TEST_RUNNER_TARGET = $(BIN_DIR)/test_runner

SRCS = $(SRC_DIR)/main.c $(MATRIX_DIR)/matrix.c $(OUTPUT_DIR)/output.c $(TESTS_DIR)/tests_matrix.c $(TESTS_DIR)/tests_output.c $(TESTS_DIR)/tests_main.c

$(TARGET_MAIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET_MAIN)

$(TEST_RUNNER_TARGET): $(TEST_OBJ) $(TESTS_DIR)/test_runner.c
	$(CC) $(CFLAGS) $(TEST_OBJ) $(TESTS_DIR)/test_runner.c -o $(TEST_RUNNER_TARGET) -lcunit

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MATRIX_DIR)/%.o: $(MATRIX_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT_DIR)/%.o: $(OUTPUT_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test_cunit: $(TEST_RUNNER_TARGET)
	./$(TEST_RUNNER_TARGET)

cppcheck:
	cppcheck --enable=all --suppress=missingInclude --suppress=missingIncludeSystem --platform=unix64 $(SRCS)

lint: cppcheck
	@echo "Проверка cppcheck завершена."

format:
	clang-format -style=LLVM -i src/*.c src/matrix/*.h src/matrix/*.c src/output/*.h src/output/*.c tests/*.c include/*.h

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET_MAIN) $(TEST_RUNNER_TARGET)

rebuild: clean $(TARGET_MAIN) $(TEST_RUNNER_TARGET)

help:
	@echo "Доступные команды:"
	@echo "  make              - Сборка основного проекта"
	@echo "  make test_cunit   - Сборка и запуск тестов"
	@echo "  make cppcheck     - Проверка кода с помощью cppcheck"
	@echo "  make lint         - Проверка стиля кода"
	@echo "  make format       - Форматирование кода"
	@echo "  make clean        - Очистка проекта"
	@echo "  make rebuild      - Полная пересборка проекта"
	@echo "  make help         - Вывод списка доступных команд"
