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

hello_world: hello_world.c
	gcc -o $@ $^

hello_world-syscall: hello_world-syscall.c
	gcc -o $@ $^

hello_world-int.o: hello_world-int.S
	as -o $@ $^

hello_world-int: hello_world-int.o
	ld -o $@ $^

run: hello_world hello_world-syscall hello_world-int
	echo

	echo 'Run hello_world'
	./hello_world
	echo

	echo 'Run hello_world-syscall'
	./hello_world-syscall
	echo

	echo 'Run hello_world-int'
	./hello_world-int
	echo

clean:
	rm -f hello_world hello_world-syscall hello_world-int.o hello_world-int
