# FileName:   Makefile
# Author:     Fasion Chan
# @contact:   fasionchan@gmail.com
# @version:   $Id$
#
# Description:
#
# Changelog:
#

.DEFAULT_GOAL := run

write.o: write.c
	gcc -c -o $@ $^

write: write.o
	gcc -o $@ $^

run: write
	./write first_file.txt 'Hello, world!'

clean:
	rm -f write write.o
