#!/bin/sh -ex

rm -rfv build
mkdir -p build

avr-gcc -nostartfiles -nodefaultlibs -nolibc -nostdlib -ffreestanding -mmcu=atmega328p -o blink blink.s
avr-objcopy -j .text -j .data -O ihex blink blink.hex

avr-gcc -g -Os -mmcu=atmega328p -o blinkBad blinkBad.c
avr-objcopy -j .text -j .data -O ihex blinkBad blinkBad.hex

avr-gcc -g -Os -mmcu=atmega328p -o blinkBad2 blinkBad2.c
avr-objcopy -j .text -j .data -O ihex blinkBad2 blinkBad2.hex

avr-gcc -g -Os -mmcu=atmega328p -o blinkBetter blinkBetter.c
avr-objcopy -j .text -j .data -O ihex blinkBetter blinkBetter.hex

avr-gcc -g -Os -mmcu=atmega328p -o blinkUART blinkUART.c
avr-objcopy -j .text -j .data -O ihex blinkUART blinkUART.hex

java -jar com.io7m.xstructural.cmdline-1.3.0-SNAPSHOT-main.jar epub --outputDirectory build --sourceFile book.xml
java -jar com.io7m.xstructural.cmdline-1.3.0-SNAPSHOT-main.jar xhtml --outputDirectory build --sourceFile book.xml
java -jar com.io7m.xstructural.cmdline-1.3.0-SNAPSHOT-main.jar xhtml --stylesheet MULTIPLE_FILE --outputDirectory build --sourceFile book.xml

mv build/output.epub build/book.epub

cp *.css build/
cp *.png build/
cp *.jpg build/
