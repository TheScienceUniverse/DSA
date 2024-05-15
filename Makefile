all: ./bin/dsa ./bin/test

./bin/dsa: main.c ./include/string.h ./include/data.h ./lib/string.o ./lib/data.o ./lib/list.o ./lib/node.o ./lib/linked_list.o ./lib/stack.o ./lib/queue.o ./lib/tree.o
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

./lib/linked_list.o: ./include/linked_list.h ./src/linked_list.c
	@echo "-> Creating lib object file for Data..."
	gcc -Wall -Werror -o ./lib/linked_list.o -c ./src/linked_list.c
	@echo "...Done"

./lib/stack.o: ./include/stack.h ./src/stack.c
	@echo "-> Creating lib object file for Data..."
	gcc -Wall -Werror -o ./lib/stack.o -c ./src/stack.c
	@echo "...Done"

./lib/queue.o: ./include/queue.h ./src/queue.c
	@echo "-> Creating lib object file for Data..."
	gcc -Wall -Werror -o ./lib/queue.o -c ./src/queue.c
	@echo "...Done"

./lib/tree.o: ./include/tree.h ./src/tree.c
	@echo "-> Creating lib object file for Data..."
	gcc -Wall -Werror -o ./lib/tree.o -c ./src/tree.c
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
