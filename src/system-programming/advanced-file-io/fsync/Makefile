# FileName:   Makefile
# Author:     Fasion Chan
# @contact:   fasionchan@gmail.com
# @version:   $Id$
#
# Description:
#
# Changelog:
#

.DEFAULT_GOAL := append

append.o: append.c
	gcc -c -o $@ $^

append: append.o
	gcc -o $@ $^

clean:
	rm -f append.o append
