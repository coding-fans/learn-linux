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

say.o: say.c
	gcc -o say.o -c say.c

hello_world.o: hello_world.c
	gcc -o hello_world.o -c hello_world.c

hello_world: say.o hello_world.o
	gcc -o hello_world say.o hello_world.o

run: hello_world
	./hello_world

clean:
	rm -f *.o
	rm -f hello_world
