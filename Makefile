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
OPTIMIZATION = -O0
OBJECT_NAMES = string data list node linked_list stack queue tree graph
OBJECTS := $(foreach f_name, $(OBJECT_NAMES), $(LIBDIR)/$(f_name).o)
TSTECTS := $(foreach f_name, $(OBJECT_NAMES), $(TSTDIR)/$(f_name).o)
EXECUTABLE := $(EXEDIR)/dsa
TSTCUTABLE := $(EXEDIR)/test
CFLAGS = -Wall -Wextra -g $(INCDIR) $(OPTIMIZATION)
CFLAGS_EXTRA = -fpic

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo "-> Linking all object files and generating executable binary file ..."
	@$(CC) $(CFLAGS) -o $@ $(CFLAGS_EXTRA) $^ ./main.c
	@chmod +x $(EXECUTABLE)
#	@echo "... Done!"
#	@echo

$(LIBDIR)/%.o: $(SRCDIR)/%.c
	@echo " + Compiling "$*" ..."
	@$(CC) $(CFLAGS) -o $@ -c $(CFLAGS_EXTRA) $^
#	@echo "... Done!"
#	@echo

$(TSTCUTABLE): $(TSTECTS)
	@echo "-> Linking all object files and generating test binary file ..."
	@$(CC) $(CFLAGS) -o $@ $(CFLAGS_EXTRA) $^ ./test/main.c
	@chmod +x $(TSTCUTABLE)
#	@echo "... Done!"
#	@echo

$(TSTDIR)/%.o: $(TSTDIR)/%.c
	@echo " + Compiling "$*" ..."
	@$(CC) $(CFLAGS) -o $@ -c $(CFLAGS_EXTRA) $^
#	@echo "... Done!"
#	@echo


.PHONY: clean

clean:
	@echo "-> Removing everything but source files ..."
	@-rm -f $(OBJECTS) $(EXECUTABLE)
	@echo "... Done"
#	@echo

