CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g -pedantic
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname)

ifeq ($(OS), Linux)
#-lsubunit
	CHECKFLAGS=-lpthread -lcheck -pthread -lrt -lm -lsubunit
else
	CHECKFLAGS=-lcheck -lm -lpthread
endif

all: clean install dist dvi gcov_report check_style leaks clean

rebuild: clean all

install: uninstall
	mkdir build
	cp Calculator.pro build
	cp -rf *.c build
	cp -rf *.cpp build
	cp -rf *.h build
	cp -rf *.ui build
	cd build && qmake Calculator.pro
	make -C build
	cd build && make clean

uninstall:
	rm -rf build
	make clean

dvi:
	open ./readme.txt

dist: install
	tar -cvf build/Сalculator.tar build
	gzip build/Сalculator.tar
	mv build/Сalculator.tar.gz ./

test: clean
	$(CC) $(CFLAGS)  *.c -o  test.out -lgcov --coverage $(CHECKFLAGS) 
	./test.out


gcov_report: test
	lcov -t "test" -o report.info -c -d . 
	genhtml -o gcov_report/ report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./gcov_report/index.html

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.c
	clang-format -i *.h
	clang-format -i *.cpp
	rm -rf .clang-format

check_style:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c >> logfile.log
	clang-format -n *.h >> logfile.log
	clang-format -n *.cpp >> logfile.log
	clang-format -n *.h >> logfile.log
	rm -rf .clang-format

valgrind:
	$(CC) $(CFLAGS)  *.c -o  test.out -lrt -lpthread -lm -lcheck $(CHECKFLAGS)
	 CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test.out
	 make clean

leaks: test
	CK_FORK=no leaks --atExit -- ./test.out >> logfile.log #leaks --atExit --
	make clean
	
clean:
	rm -rf *.o \
		*.a \
		*.app \
		*.so \
		*.gcno \
		*gcda \
		*.gcov \
		gcov_report.* \
		*.dSYM \
        RESULT_VALGRIND.txt \
		*.out \
        unit-test \
        vtests_run \
		run \
		gcov \
		report/ \
		gcov_report/ \
		report.info \
		gcov_report \
		gcov_test \
		*.log

