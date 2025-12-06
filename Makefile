VPATH := ./inc ./src ./obj ./lib
vpath %.h ./inc
vpath %.c ./src
vpath %.o ./obj
vpath %.so ./lib

CC = gcc
INCDIR = -I.
SRCDIR = ./src
OBJDIR = ./obj
LIBDIR = ./lib
EXEDIR = ./bin
TSTDIR = ./tst
LOGDIR = ./log
COVDIR = ./cov
BLDDIR = ./
OPTIMIZATION = -O0
OBJECT_NAMES = basic stream string data chunk bare_list list iterator node linked_list stack queue tree #graph
OBJECTS := $(foreach f_name, $(OBJECT_NAMES), $(OBJDIR)/$(f_name).o)
TSTECTS := $(foreach f_name, $(OBJECT_NAMES), $(OBJDIR)/test_$(f_name).o)
MGCECTS := $(OBJDIR)/mgc.o
EXECUTABLE := $(EXEDIR)/dsa
TSTCUTABLE := $(EXEDIR)/tst
MEMCUTABLE := $(EXEDIR)/mem
BDGCUTABLE := $(EXEDIR)/bdg
LIBRARY := $(LIBDIR)/libdsa.so
CFLAGS = -Wall -Wextra -g $(INCDIR) $(OPTIMIZATION)# -fanalyzer
CFLAGS_EXTRA = -fPIC -shared -finput-charset=UTF-8# [1] position-indepedent-code, [2] shared object, [3] input character encoding UTF-8
CFLAGS_COVERAGE = --coverage

all: $(EXECUTABLE) $(TSTCUTABLE) $(MEMCUTABLE) $(BDGCUTABLE) $(LIBRARY)

$(EXECUTABLE): ./main.c $(OBJECTS) $(MGCECTS)
	@echo "-> Linking all object files and generating executable binary file ..."
	@$(CC) $(CFLAGS) -o $@ $^
	@chmod +x $(EXECUTABLE)
#	@echo "... Done!"
#	@echo

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo " + Compiling "$*" ..."
	@$(CC) $(CFLAGS) $(CFLAGS_EXTRA) -o $@ -c $^
#	@echo "... Done!"
#	@echo

$(MGCECTS): $(SRCDIR)/mgc.c
	@echo " + Compiling "$*" ..."
	@$(CC) $(CFLAGS) $(CFLAGS_EXTRA) -o $@ -c $^

test: $(TSTCUTABLE)

$(TSTCUTABLE): ./test.c $(OBJECTS) $(TSTECTS) $(MGCECTS)
	@echo "-> Linking all object files and generating test binary file ..."
	@$(CC) $(CFLAGS) $(CFLAGS_COVERAGE) -o $@ $^
	@chmod +x $(TSTCUTABLE)
#	@echo "... Done!"
#	@echo

$(OBJDIR)/test_%.o: $(TSTDIR)/%.c
	@echo " + Compiling test_"$*" ..."
	@$(CC) $(CFLAGS) $(CFLAGS_EXTRA) $(CFLAGS_COVERAGE) -o $@ -c $^
#	@echo "... Done!"
#	@echo

$(MEMCUTABLE): ./mem.c $(OBJECTS) $(MGCECTS)
	@echo "-> Linking all object files and generating memory logger binary file ..."
	@$(CC) $(CFLAGS) -o $@ $^
	@chmod +x $(MEMCUTABLE)
#	@echo "... Done!"
#	@echo

$(BDGCUTABLE): shield.c
	@echo "-> Creating badge (shield) crafter program ..."
	@$(CC) $(CFLAGS) -o $@ $^

$(LIBRARY): $(OBJECTS) $(MGCECTS)
	@gcc $(CFLAGS) $(CFLAGS_EXTRA) -o $@ $^


.PHONY: clean again check flow memlog memclear ccov

clean:
	@echo "-> Removing generated files ..."
	@-rm -f $(OBJECTS) $(MGCECTS) $(EXECUTABLE) $(TSTCUTABLE) $(LIBRARY)
	@-rm -f ./obj/* ./lib/* ./bin/* ./log/* ./cov/* ./aft/*
	@echo "... Done"
#	@echo

again:
	@make clean && make all
	@touch ./log/memory.log

check:
	@tabs 4
	@$(TSTCUTABLE) | tee $(LOGDIR)/test.log
	@echo "-> Checking test status..."
	@echo $$[$$[$$(cat log/test.log | grep -c "PASSED") * 100] / $$(cat log/test.log | grep -c -E "PASSED|FAILED")] > $(LOGDIR)/passmark.log
	@$(BDGCUTABLE) shield tests $$(if [ `cut -d' ' -f1 ./log/passmark.log` -gt "79" ]; then echo "passing"; else echo "failing"; fi)
	@mv -f shield ./aft/test_status.svg

memlog:
	@echo "-> Displaying memory log file in readable format..."
	@./bin/mem show

memcheck:
	@echo "-> Check counts of leftout memory for each data-structures..."
	@./bin/mem check

ccov:
	@echo "-> Calculating code coverage..."
	@find ./obj/ ! -name '*.o' -type f | xargs -r cp -t cov/
	@find ./obj/ ! -name '*.o' -type f | xargs -r rm -f
	@mv ./bin/*.gcda ./bin/*.gcno ./cov/
	@-rm -f $(LOGDIR)/all_cov.log
	@-rm -f $(LOGDIR)/all_cov_cnt.log
	@-rm -f $(LOGDIR)/coverage.log

	@for f in $(foreach f_name, $(OBJECT_NAMES), $(COVDIR)/test_$(f_name)); \
	do \
		gcov -abcf "$$f" >> $(LOGDIR)/all_cov.log || exit 1; \
		echo >> $(LOGDIR)/all_cov.log; \
	done

	@grep "%" $(LOGDIR)/all_cov.log \
		| awk -F' |:' '{print $$(NF-2)}' \
		| sed 's/.$$//' \
		>> $(LOGDIR)/all_cov_cnt.log || exit 1;

	@awk '{sum+=($$1)} END {print int(sum/NR)}' $(LOGDIR)/all_cov_cnt.log > $(LOGDIR)/coverage.log
	@mv *.gcov $(COVDIR)
	@./bin/bdg shield coverage `cut -d' ' -f1 ./log/coverage.log`%
	@mv -f shield ./aft/code_coverage.svg

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
