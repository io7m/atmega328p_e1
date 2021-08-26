#!/bin/sh -ex

rm -rf build

mkdir -p build

SOURCES="
io_register.h
main.c
usart.h
usart.c
timer8.h
timer16.h
"

for SOURCE in ${SOURCES}
do
  clang-format -i "${SOURCE}"
done

./c-compile build/usart.o usart.c
./c-compile build/main.o main.c
./c-link build/main build/main.o build/usart.o
./hex build/main.hex build/main
./size build/main
