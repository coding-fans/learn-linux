# FileName:   Makefile
# Author:     Fasion Chan
# @contact:   fasionchan@gmail.com
# @version:   $Id$
#
# Description:
#
# Changelog:
#

daemonize.o: daemonize.c
	gcc -c -o $@ $^

echo.o: echo.c
	gcc -c -o $@ $^

echo: echo.o
	gcc -o $@ $^

echod.o: echod.c
	gcc -c -o $@ $^

echod: daemonize.o echod.o
	gcc -o $@ $^

all: echo echod

clean:
	rm -rf *.o
	rm -rf echo echod
