DIRECTORY=3d_viewer_v2/model
SOURCES=$(shell find $(DIRECTORY) -name '*.cc')
HEADERS=$(shell find $(DIRECTORY) -name '*.h')
OBJ=$(SOURCES:.cc=.o)
LIB_NAME=s21_3D_Viewer.a

CC=g++ -g
CFLAGS=-std=c++17
FLAG1=-I 3d_viewer_v2
FLAG2=-c
COV_FLAGS = -fprofile-arcs -ftest-coverage
OPEN=
TC_FLAGS=
LEAK_CHECK=
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	OPEN= xdg-open
    CC += -D LINUX -m64
	TC_FLAGS += -lcheck -lsubunit -lm -lrt -lpthread 
	LEAK_CHECK +=CK_FORK=no valgrind --trace-children=yes --track-fds=yes --leak-check=yes --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind_log.txt ./test.out
endif
ifeq ($(UNAME_S),Darwin)
    CC += -D OSX
	#TC_FLAGS += -lcheck -lm -lpthread
	TC_FLAGS += -lm -lpthread
	LEAK_CHECK +=CK_FORK=no leaks -atExit -- ./test.out
	OPEN= open
endif

default: all

all: clean test $(LIB_NAME)

test: clean $(LIB_NAME)
	$(CC) $(FLAG1) $(CFLAGS) $(COV_FLAGS) test.cc $(LIB_NAME) -o test.out $(TC_FLAGS) -lgtest -lgtest_main
	./test.out

$(LIB_NAME): $(HEADERS) $(OBJ)
	ar rcs $(LIB_NAME) $(OBJ)
	ranlib $(LIB_NAME)

%.o: %.cc
	$(CC) $(FLAG1) $(CFLAGS) $(FLAG2) $(COV_FLAGS) $< -o $@

clean:
	find . \( -name "*.a" -o -name "*.o"  -o -name "*.tar" -o -name "*.out" -o -name "*.info" -o -name "*.gcno" -o -name "*.gcda" -o -name "report" -o -name "*.cfg" -o -name "*.gcov" \) -not -name "fortests.txt" -delete
	find . -type d -name 'build*' -exec rm -rf {} +
	rm -rf report

check:
	find . -type f \( -name "*.cc" -o -name "*.h" \) -exec clang-format -style=google -i {} +
	$(LEAK_CHECK)

dist: clean
	touch ./3d_viewer_dist.tar
	git archive --output=./3d_viewer_dist.tar develop

install: clean create_build_dir
	@cd ./3d_viewer_v2; qmake -o ../build
	@make -C ./build -f Makefile

create_build_dir:
	@mkdir -p ./build

uninstall:
	find . -type d -name 'build*' -exec rm -rf {} +

dvi:
	$(OPEN) ./documentation/html/index.html

gcov_report: clean test
	lcov --no-external -t "test" -o test_list.info -c -d .
	genhtml -o report test_list.info
	@$(OPEN) ./report/index.html
