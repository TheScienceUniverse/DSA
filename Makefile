VPATH := ./include ./src ./obj ./lib
vpath %.h ./include
vpath %.c ./src
vpath %.o ./obj
vpath %.so ./lib

CC = gcc
INCDIR = -I.
SRCDIR = ./src
OBJDIR = ./obj
LIBDIR = ./lib
EXEDIR = ./bin
TSTDIR = ./test
LOGDIR = ./log
COVDIR = ./cov
BLDDIR = ./
OPTIMIZATION = -O0
OBJECT_NAMES = basic string data chunk bare_list list iterator node linked_list stack queue tree#graph
OBJECTS := $(foreach f_name, $(OBJECT_NAMES), $(OBJDIR)/$(f_name).o)
TSTECTS := $(foreach f_name, $(OBJECT_NAMES), $(OBJDIR)/test_$(f_name).o)
EXECUTABLE := $(EXEDIR)/dsa
TSTCUTABLE := $(EXEDIR)/test
MEMCUTABLE := $(EXEDIR)/mem
BDGCUTABLE := $(EXEDIR)/bdg
LIBRARY := $(LIBDIR)/libdsa.so
CFLAGS = -Wall -Wextra -g $(INCDIR) $(OPTIMIZATION)
CFLAGS_EXTRA = -fPIC -shared -finput-charset=UTF-8# [1] position-indepedent-code -finput-charset=UTF-8
CFLAGS_COVERAGE = --coverage

all: $(EXECUTABLE) $(TSTCUTABLE) $(MEMCUTABLE) $(BDGCUTABLE) $(LIBRARY)

$(EXECUTABLE): $(OBJECTS)
	@echo "-> Linking all object files and generating executable binary file ..."
	@$(CC) $(CFLAGS) -o $@ $^ ./main.c
	@chmod +x $(EXECUTABLE)
#	@echo "... Done!"
#	@echo

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo " + Compiling "$*" ..."
	@$(CC) $(CFLAGS) $(CFLAGS_EXTRA) -o $@ -c $^
#	@echo "... Done!"
#	@echo

test: $(TSTCUTABLE)

$(TSTCUTABLE): $(TSTECTS)
	@echo "-> Linking all object files and generating test binary file ..."
	@$(CC) $(CFLAGS) $(CFLAGS_COVERAGE) -o $@ ./test.c $(OBJECTS) $^
	@chmod +x $(TSTCUTABLE)
#	@echo "... Done!"
#	@echo

$(OBJDIR)/test_%.o: $(TSTDIR)/%.c
	@echo " + Compiling test_"$*" ..."
	@$(CC) $(CFLAGS) $(CFLAGS_EXTRA) $(CFLAGS_COVERAGE) -o $@ -c $^
#	@echo "... Done!"
#	@echo

$(MEMCUTABLE): $(OBJECTS) mem.c
	@echo "-> Linking all object files and generating memory logger binary file ..."
	@$(CC) $(CFLAGS) -o $@ ./mem.c $(OBJDIR)/basic.o $(OBJDIR)/string.o
	@chmod +x $(MEMCUTABLE)
#	@echo "... Done!"
#	@echo

$(BDGCUTABLE): shield.c
	@echo "-> Creating badge (shield) crafter program ..."
	@$(CC) $(CFLAGS) -o $@ $^

$(LIBRARY): $(OBJECTS)
	@gcc $(CFLAGS) $(CFLAGS_EXTRA) -o $@ $^

.PHONY: clean again check flow memlog ccov

clean:
	@echo "-> Removing generated files ..."
	@-rm -f $(OBJECTS) $(EXECUTABLE) $(TSTCUTABLE) $(LIBRARY)
	@-rm -f ./obj/* ./lib/* ./bin/* ./log/* ./cov/* ./aft/*
	@echo "... Done"
#	@echo

again:
	@make clean && make all

check:
	@./bin/test | tee $(LOGDIR)/test.log
	echo $$[$$[`cat log/test.log | grep -c "PASSED"` * 100] / `cat log/test.log | grep -c -E "PASSED|FAILED"`] > $(LOGDIR)/passmark.log
	./bin/bdg shield tests $$(if [ `cut -d' ' -f1 ./log/passmark.log` -gt "79" ]; then echo "passing"; else echo "failing"; fi)
	@mv -f shield ./aft/test_status.svg

memlog:
	./bin/mem show

ccov:
	@find ./obj/ ! -name '*.o' -type f | xargs -r cp -t cov/
	@find ./obj/ ! -name '*.o' -type f | xargs -r rm -f
	@mv ./bin/*.gcda ./bin/*.gcno ./cov/
	@-rm -f $(LOGDIR)/all_cov.log
	@-rm -f $(LOGDIR)/all_cov_cnt.log
	@-rm -f $(LOGDIR)/coverage.log

	for f in $(foreach f_name, $(OBJECT_NAMES), $(COVDIR)/test_$(f_name)); \
	do \
		gcov -abcf "$$f" >> $(LOGDIR)/all_cov.log || exit 1; \
		echo >> $(LOGDIR)/all_cov.log; \
	done

	grep "%" $(LOGDIR)/all_cov.log \
		| awk -F' |:' '{print $$(NF-2)}' \
		| sed 's/.$$//' \
		>> $(LOGDIR)/all_cov_cnt.log || exit 1;

	@awk '{sum+=($$1)} END {print int(sum/NR)}' $(LOGDIR)/all_cov_cnt.log > $(LOGDIR)/coverage.log
	@mv *.gcov $(COVDIR)
	./bin/bdg shield coverage `cut -d' ' -f1 ./log/coverage.log`%
	mv -f shield ./aft/code_coverage.svg

flow:
	@tabs 4;
	@echo "	basic";
	@echo "	|";
	@echo "	+->	string";
	@echo "		|";
	@echo "		+->	data";
	@echo "			|";
	@echo "			+->	chunk";
	@echo "				|";
	@echo "				+->	list";
	@echo "				+->	list2";
	@echo "					|";
	@echo "					+->	node";
	@echo "						|";
	@echo "						+->	linked_list";
	@echo "							|";
	@echo "							+->	stack";
	@echo "							+->	queue";
	@echo "								|";
	@echo "								+->	tree";
	@echo "								+->	graph";
