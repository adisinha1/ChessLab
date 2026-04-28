CC=g++
C_FLAGS=-g -std=c++17 -Wall -fsanitize=address,undefined

SRC_FILES=$(filter-out $(wildcard main.cc),$(wildcard *.cc))
APP=chess

custom_tests:
	$(CC) $(C_FLAGS) $(SRC_FILES) main.cc -o $(APP)

valgrind:
	valgrind --leak-check=full ./$(APP) $(TEST)

