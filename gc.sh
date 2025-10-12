rm ./log/memory.log
touch ./log/memory.log
sh ./check_datatype.sh "data"

make
rm -rf ./bin/mem
gcc -Wall -o ./bin/mem ./mem.c ./obj/basic.o ./obj/string.o ./obj/chunk.o ./obj/list.o ./obj/iterator.o ./obj/data.o

./bin/mem show
./bin/mem clear
