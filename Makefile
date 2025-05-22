VPATH := ./include ./src ./lib
vpath %.h ./include
vpath %.c ./src
vpath %.o ./lib

CC = gcc
INCDIR = -I.
SRCDIR = ./src
LIBDIR = ./lib
EXEDIR = ./bin
TSTDIR = ./test
LOGDIR = ./log
BLDDIR = ./
OPTIMIZATION = -O0
OBJECT_NAMES = basic string data chunk bare_list list iterator node linked_list stack queue tree#graph
OBJECTS := $(foreach f_name, $(OBJECT_NAMES), $(LIBDIR)/$(f_name).o)
TSTECTS := $(foreach f_name, $(OBJECT_NAMES), $(LIBDIR)/test_$(f_name).o)
EXECUTABLE := $(EXEDIR)/dsa
TSTCUTABLE := $(EXEDIR)/test
MEMCUTABLE := $(EXEDIR)/mem
CFLAGS = -Wall -Wextra -g $(INCDIR) $(OPTIMIZATION)
CFLAGS_EXTRA = -fPIC -shared# [1] position-indepedent-code -finput-charset=UTF-8

all: $(EXECUTABLE) $(TSTCUTABLE) $(MEMCUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo "-> Linking all object files and generating executable binary file ..."
	@$(CC) $(CFLAGS) -o $@ $^ ./main.c
	@chmod +x $(EXECUTABLE)
#	@echo "... Done!"
#	@echo

$(LIBDIR)/%.o: $(SRCDIR)/%.c
	@echo " + Compiling "$*" ..."
	@$(CC) $(CFLAGS) $(CFLAGS_EXTRA) -o $@ -c $^
#	@echo "... Done!"
#	@echo

test: $(TSTCUTABLE)

$(TSTCUTABLE): $(TSTECTS)
	@echo "-> Linking all object files and generating test binary file ..."
	@$(CC) $(CFLAGS) -o $@ ./test.c $(OBJECTS) $^
	@chmod +x $(TSTCUTABLE)
#	@echo "... Done!"
#	@echo

$(LIBDIR)/test_%.o: $(TSTDIR)/%.c
	@echo " + Compiling test_"$*" ..."
	@$(CC) $(CFLAGS) $(CFLAGS_EXTRA) -o $@ -c $^
#	@echo "... Done!"
#	@echo

$(MEMCUTABLE): $(OBJECTS) mem.c
	@echo "-> Linking all object files and generating memory logger binary file ..."
	@$(CC) $(CFLAGS) -o $@ ./mem.c $(LIBDIR)/basic.o $(LIBDIR)/string.o
	@chmod +x $(MEMCUTABLE)
#	@echo "... Done!"
#	@echo


.PHONY: clean again check memlog flow

clean:
	@echo "-> Removing generated files ..."
	@-rm -f $(OBJECTS) $(EXECUTABLE) $(TSTCUTABLE)
	@-rm -f ./lib/* ./bin/* ./log/*
	@echo "... Done"
#	@echo

again:
	@make clean && make

check:
	./bin/test show

memlog:
	./bin/mem show

flow:
	@tabs 4
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
