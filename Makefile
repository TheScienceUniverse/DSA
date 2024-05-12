all: ./bin/dsa ./bin/test

./bin/dsa: main.c ./include/string.h ./include/data.h ./lib/string.o ./lib/data.o ./lib/list.o ./lib/node.o
	@echo "-> Building main executable..."
	gcc -Wall -Werror -o ./bin/dsa ./lib/*.o main.c
	@echo "...Done"

./lib/string.o: ./include/string.h ./src/string.c
	@echo "-> Creating lib object file for String..."
	gcc -Wall -Werror -o ./lib/string.o -c ./src/string.c
	@echo "...Done"

./lib/data.o: ./include/data.h ./src/data.c
	@echo "-> Creating lib object file for Data..."
	gcc -Wall -Werror -o ./lib/data.o -c ./src/data.c
	@echo "...Done"

./lib/list.o: ./include/list.h ./src/list.c
	@echo "-> Creating lib object file for Data..."
	gcc -Wall -Werror -o ./lib/list.o -c ./src/list.c
	@echo "...Done"

./lib/node.o: ./include/node.h ./src/node.c
	@echo "-> Creating lib object file for Data..."
	gcc -Wall -Werror -o ./lib/node.o -c ./src/node.c
	@echo "...Done"

./bin/test: ./test/main.c
	@echo "-> Building test executable..."
	gcc -Wall -Werror -o ./bin/test ./lib/*.o ./test/main.c
	@echo "...Done"

PHONY: clean

clean:
	@echo "-> Removing everything but source files..."
	rm ./bin/* ./lib/*
	@echo "...Done"
	@echo
