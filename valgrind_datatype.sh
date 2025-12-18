#!/bin/sh

rm ./log/memory.log
rm ./vgcore.*
make again
tabs 4
valgrind ./bin/tst "$@"
