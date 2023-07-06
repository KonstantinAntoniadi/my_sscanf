CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
OS := $(shell uname)

ifeq ($(OS),Linux)
TEST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
else
TEST_LIBS = -lcheck -lm -lpthread -fprofile-arcs -ftest-coverage
endif

all: clean my_sscanf.a test

test: clean my_sscanf.a
	gcc unit_test.c my_sscanf.c my_sscanf.a $(TEST_LIBS) -o unit_test
	./unit_test

my_sscanf.a: my_sscanf.o
	ar -crs my_sscanf.a my_sscanf.o

my_sscanf.o:
	gcc $(FLAGS) -c my_sscanf.c

clean:
	rm -rf *.o *.a
	rm -rf *.gcno *.gcda
	rm -rf unit_test

rebuild: clean all
