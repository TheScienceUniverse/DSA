./bin/dsa: main.c ./include/basic.h ./lib/string.o
	@echo "-> Creating final executable file..."
	gcc -Wall -Werror -o ./bin/dsa ./lib/string.o main.c
	@echo "...Done"

./lib/string.o: ./include/string.h ./src/string.c
	@echo "-> Creating lib object file for String..."
	gcc -Wall -Werror -o ./lib/string.o -c ./src/string.c
	@echo "...Done"

.PHONY: clean test

clean:
	@echo "-> Removing everything but source files..."
	rm ./bin/* ./lib/* ./test/a.out
	@echo "...Done"
	@echo

test:
	@echo "-> Removing test executable..."
	gcc -Wall -Werror -o ./test/a.out ./lib/*.o ./test/main.c
	@echo "...Done"
