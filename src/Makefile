CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
OS := $(shell uname)

ifeq ($(OS),Linux)
TEST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
else
TEST_LIBS = -lcheck -lm -lpthread -fprofile-arcs -ftest-coverage
endif

all: clean s21_sscanf.a test

test: clean s21_sscanf.a
	gcc unit_test.c s21_sscanf.c s21_sscanf.a $(TEST_LIBS) -o unit_test
	./unit_test

s21_sscanf.a: s21_sscanf.o
	ar -crs s21_sscanf.a s21_sscanf.o

s21_sscanf.o:
	gcc $(FLAGS) -c s21_sscanf.c

clean:
	rm -rf s21_string
	rm -rf *.o *.a
	rm -rf *.gcno *.gcda
	rm -rf unit_test

rebuild: clean all
