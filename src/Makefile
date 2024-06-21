CC=gcc
CXXFLAGS=-Wall -Wextra -Werror -Wno-unused -pedantic -std=c++17
GTESTFLAGS=-lgtest_main -lgtest -lpthread
#
NAME=s21_matrix_oop.a
HEADER=s21_matrix_oop.h
SRC=s21_matrix_oop.cc
OBJ=$(patsubst %.cc, %.o, $(SRC))

LIBGTEST=g_test.a
HEADERGTEST=g_test.h
SRCGTEST=g_test.cc
OBJGTEST=$(patsubst %.cc, %.o, $(SRCGTEST))
#
OS = $(shell uname)
#
.PHONY: all s21_matrix_oop g_test test check gcov_report re clean m
#
#
#
all: $(NAME)
#
build: $(NAME)
#
$(NAME) : $(OBJ) $(HEADER)
	ar rcs $(NAME) $?
%.o : %.cc $(HEADER)
	$(CC) $(CXXFLAGS) -c $< -o $@
#
$(LIBGTEST) : $(OBJ) $(HEADERGTEST)
	ar rcs $(LIBGTEST) $?
%.o : %.cc $(LIBGTEST)
	$(CC) $(CXXFLAGS) -c $< -o $@
#
test: build $(LIBGTEST)
	$(CC) $(GTESTFLAGS) $(CXXFLAGS) -lstdc++ $(SRCGTEST) $(LIBGTEST) $(SRC) $(NAME) -o test
	./test
#
check: test
	clang-format -n *.cc *.h
	leaks -atExit -- test
#
re: clean build
#
clean:
	rm -rf *.o *.gch *.out *.a MATRIX_OOP test
#
m: build
	$(CC) main.cc s21_matrix_oop.cc $(NAME) $(CXXFLAGS) -lstdc++ -o MATRIX_OOP
	MATRIX_OOP
