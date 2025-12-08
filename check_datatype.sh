#!/bin/sh

make again
rm ./log/memory.log
tabs 4
./bin/tst "$@"
