./bin/dsa: main.c ./include/basic.h
	@echo "-> Creating final executable file..."
	gcc -Wall -Werror -o ./bin/dsa main.c
	@echo "...Done"

.PHONY: clean test

clean:
	@echo "-> Removing everything but source files..."
	rm ./bin/dsa
	@echo "...Done"
	@echo

test:
	@echo "-> Removing test executable..."
	gcc -Wall -Werror -o ./test/a.out ./test/main.c
	@echo "...Done"
