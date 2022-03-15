CFLAGS=-std=c++20 -Wall -Wextra -Werror
TESTFLAGS=-lgtest
CC=g++
EXEC_NAME=matrix.out

SOURCES_LIB=s21_matrix.cpp s21_support_funcs.cpp
OBJECTS_LIB=$(SOURCES_LIB:.cpp=.o)


.PHONY: all clean test gcov_report

all: s21_matrix_oop.a test gcov_report 

s21_matrix_oop.a:
	$(CC) $(CFLAGS) $(SOURCES_LIB) -c
	ar -rcs s21_matrix_oop.a $(OBJECTS_LIB)

leaks: s21_matrix_oop.a
	CK_FORK=no leaks --atExit -- ./$(EXEC_NAME)

clean:
	rm -rf *.out *.o s21_matrix_oop.a *.gcda *.gcno *.info 
	-rm -rf report

test: s21_matrix_oop.a
	$(CC) $(CFLAGS) s21_test.cpp s21_matrix_oop.a -o test.out -lgtest
	./test.out

gcov_report:
	$(CC) s21_test.cpp s21_support_funcs.cpp -c
	$(CC) --coverage  s21_matrix.cpp s21_support_funcs.o s21_test.o -o test.out $(TESTFLAGS)
	./test.out
	lcov -t "test" -o test.info -c -d ./
	genhtml -o report test.info
	open report/index.html


run: s21_matrix_oop.a
	$(CC) $(CFLAGS) main.cpp s21_matrix_oop.a -o $(EXEC_NAME)
	./$(EXEC_NAME)

cpplint:
	@echo "-----cpplint-----"
	@python3 ../materials/linters/cpplint.py --extensions=c *.cpp
	@echo "-----------------"
	@echo

cppcheck:
	@echo "-----cppcheck----"
	@cppcheck --enable=all --suppress=missingIncludeSystem *.cpp
	@echo "-----------------"
	@echo

check: cpplint cppcheck